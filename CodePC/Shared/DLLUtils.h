#pragma once

#include <Windows.h>
#include <Tlhelp32.h>
#include <tchar.h>

// To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS
// and compile with -DPSAPI_VERSION=1
#pragma comment(lib, "Psapi.lib")
#define DPSAPI_VERSION (1)

static bool InjectDLL(HANDLE hProcess, const char* dllFilename)
{
	HANDLE hThread;
	char    szLibPath[_MAX_PATH];  // The name of our "LibSpy.dll" module
									// (including full path!);

	void*   pLibRemote;   // The address (in the remote process) where 
							// szLibPath will be copied to;
	//DWORD   hLibModule;   // Base address of loaded module (==HMODULE);
	HMODULE hLibModule = 0;
	HMODULE hKernel32 = ::GetModuleHandle(_T("Kernel32"));

	// initialize szLibPath
	GetFullPathNameA(dllFilename, _MAX_PATH, szLibPath, NULL);

	//MessageBoxA(0, szLibPath, "NAJS", 0);

	// 1. Allocate memory in the remote process for szLibPath
	// 2. Write szLibPath to the allocated memory
	pLibRemote = ::VirtualAllocEx( hProcess, NULL, sizeof(szLibPath),
									MEM_COMMIT, PAGE_READWRITE );
	::WriteProcessMemory( hProcess, pLibRemote, (void*)szLibPath,
							sizeof(szLibPath), NULL );

	// Load "LibSpy.dll" into the remote process
	// (via CreateRemoteThread & LoadLibrary)
	hThread = ::CreateRemoteThread( hProcess, NULL, 0,
				(LPTHREAD_START_ROUTINE) ::GetProcAddress( hKernel32, "LoadLibraryA" ),
											pLibRemote, 0, NULL );
	::WaitForSingleObject( hThread, INFINITE );

	// Get handle of the loaded module
	::GetExitCodeThread( hThread, (DWORD*)&hLibModule );

	// Clean up
	::CloseHandle( hThread );
	::VirtualFreeEx( hProcess, pLibRemote, sizeof(szLibPath), MEM_RELEASE );

	return true;
}

static bool EjectDLL(DWORD dwProcessId, const char* pszLibFile) 
{
	typedef void (*PGNSI)(void);
	typedef void (*PSetThumbDimensions)(int, int);

	typedef LONG (NTAPI *pNtSuspendProcess )( HANDLE ProcessHandle );
	typedef LONG (NTAPI *pNtResumeProcess )( HANDLE ProcessHandle );
	typedef LONG (NTAPI *pRtlAdjustPrivilege)(int,BOOL,BOOL,int*);

	HMODULE ntdll = LoadLibraryA( "ntdll.dll" );
	pRtlAdjustPrivilege RtlAdjustPrivilege = (pRtlAdjustPrivilege) GetProcAddress(ntdll,"RtlAdjustPrivilege");
	pNtSuspendProcess NtSuspendProcess = (pNtSuspendProcess)GetProcAddress( ntdll, "NtSuspendProcess" ); 
	pNtResumeProcess NtResumeProcess = (pNtResumeProcess)GetProcAddress(ntdll, "NtResumeProcess" );

     if (!dwProcessId)
          return FALSE;

     BOOL bResult = FALSE;
     HANDLE hthSnapshot = NULL;
     HANDLE hProcess = NULL, hThread = NULL;
     
    // Grab a new snapshot of the process
    if (hthSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId))
	{    
		wchar_t  wDLLname[MAX_PATH];
		swprintf(wDLLname, sizeof(wDLLname), L"%hs", pszLibFile);

		// Get the HMODULE of the desired library
		MODULEENTRY32 me = { sizeof(me) };
		BOOL fFound = FALSE;
		BOOL fMoreMods = Module32First(hthSnapshot, &me);
		for (; fMoreMods && !fFound; fMoreMods = Module32Next(hthSnapshot, &me))
		{

			fFound = (_wcsicmp(me.szModule,  wDLLname) == 0) || 
					 (_wcsicmp(me.szExePath, wDLLname) == 0);

			if(fFound == 1)
				break;
		}
		
		if (fFound)
		{
			// Get a handle for the target process.
			if (hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId))
			{
				int prtn;
				RtlAdjustPrivilege(20,TRUE,FALSE,&prtn);

				NtSuspendProcess( hProcess );

				bool notDone = true;
				while(notDone)
				{
					// Get the real address of LoadLibraryW in Kernel32.dll
					PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)
						GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "FreeLibrary");
				
					if (pfnThreadRtn)
					{ 
						// Create a remote thread that calls LoadLibraryW(DLLPathname)
						if(hThread = CreateRemoteThread(hProcess, NULL, 0, 
							pfnThreadRtn, me.modBaseAddr, 0, NULL))
						{
							// Wait for the remote thread to terminate
							if(WaitForSingleObject(hThread, INFINITE) != WAIT_FAILED)      
								bResult = TRUE; // Everything executed successfully

							BOOL res = FALSE;
							::GetExitCodeThread( hThread, (DWORD*)&res );

							notDone = (res == TRUE);

							if (hThread) 
								CloseHandle(hThread);
						}
					}
				}
			}
		}
	}

	// clean up
    if (hthSnapshot) 
        CloseHandle(hthSnapshot);

	Sleep(1000);

	NtResumeProcess( hProcess );

    if (hProcess) 
        CloseHandle(hProcess);


     return bResult == TRUE;
}