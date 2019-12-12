#include "Processes.h"

#include <locale>
#include <codecvt>
#include <string>
#include <iostream>
#include <tlhelp32.h>
#include <cstdio>
#include "../../Shared/DLLUtils.h"
#include "../HookDXGI/SharedMemory.h"

void StartInjecter(DWORD processID, char exeVersion)
{
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInformation;

	memset(&startupInfo, 0, sizeof(startupInfo));
	startupInfo.cb = sizeof(STARTUPINFO);
	auto injectorName = ((exeVersion == 64) ? L"Injecter64.exe" : L"Injecter32.exe");
	std::wstring commandLineString = std::to_wstring(processID) + L", " + std::to_wstring(static_cast<int>(exeVersion));
	//std::wcout << commandLineString << std::endl << commandLineString.length() << std::endl;
	wchar_t* commandLine = new wchar_t[commandLineString.length() + 1];

	for (unsigned int i = 0; i < commandLineString.length(); ++i)
		commandLine[i] = commandLineString[i];

	commandLine[commandLineString.length()] = L'\0';

	std::wcout << L"Starting injecter with parameters: " << std::wstring(commandLine) << std::endl;

	CreateProcessW(
		injectorName,
		commandLine,
		NULL,
		NULL,
		FALSE,
		NULL,
		NULL,
		NULL,
		&startupInfo,
		&processInformation);
}

bool StartProcess(const wchar_t* applicationName)
{
	STARTUPINFO            startupInfo;
	PROCESS_INFORMATION     processInformation;

	memset(&startupInfo, 0, sizeof(startupInfo));
	startupInfo.cb = sizeof(STARTUPINFO);

	if (CreateProcessW(
		applicationName,//L"../Demo.exe",
		NULL,
		NULL,
		NULL,
		FALSE,
		CREATE_SUSPENDED, //processen ska vila direkt, vi måste ta över först
		NULL,
		NULL,
		&startupInfo,
		&processInformation))
	{
		DWORD binaryType;
		GetBinaryTypeW(applicationName, &binaryType);

		if (binaryType == SCS_32BIT_BINARY) // 32 bit binary
			StartInjecter(processInformation.dwProcessId, 32);
		else if (binaryType == SCS_64BIT_BINARY)
			StartInjecter(processInformation.dwProcessId, 64);
		else
			std::cout << "Error, unkown exe type!\n";

		//nu är vi nog redo att låta processen köra igång igen
		Sleep(2000);

		ResumeThread(processInformation.hThread);

		//release handle
		CloseHandle(processInformation.hThread);
		CloseHandle(processInformation.hProcess);
	}
	else
	{
		std::cout << "Failed to start process\n";
		auto lastError = GetLastError();
		std::cout << "GetLastError() = " << std::to_string(lastError) << std::endl;
		MessageBoxW(0, (L"Failed to start process " + std::wstring(applicationName) + L"GetLastError() = " + std::to_wstring(lastError)).c_str(), L"", 0);
		return false;
	}

	return true;
}

void InjectThreadFunction()
{
	// Skapa en bit minne där den injectade applikationen kan skriva path till nya program som ska startas
	SharedMemory injectMemory(L"INJECTOR_MEMORY", sizeof(bool) + sizeof(DWORD) + sizeof(char), true);
	static_cast<bool*>(injectMemory.GetPointer())[0] = false;

	while (true)
	{
		if (*static_cast<bool*>(injectMemory.GetPointer()) == true)
		{
			// First part is a bool to say if there is a new program that should be started
			// Second part is a DWORD containing the process id
			// Third part is a char containing information about if the process is 32 or 64 bit

			DWORD processID = *reinterpret_cast<DWORD*>(static_cast<char*>(injectMemory.GetPointer()) + 1);
			char exeVersion = *(static_cast<char*>(injectMemory.GetPointer()) + sizeof(bool) + sizeof(DWORD));
			StartInjecter(processID, exeVersion);
			static_cast<bool*>(injectMemory.GetPointer())[0] = false; // We are done
		}
	}
}