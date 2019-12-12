#include <Windows.h>
#include <string>
#include <iostream>
#include "Injection.h"

BOOL SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
{
	LUID luid;
	BOOL bRet = FALSE;

	if (LookupPrivilegeValue(NULL, lpszPrivilege, &luid))
	{
		TOKEN_PRIVILEGES tp;

		tp.PrivilegeCount = 1;
		tp.Privileges[0].Luid = luid;
		tp.Privileges[0].Attributes = (bEnablePrivilege) ? SE_PRIVILEGE_ENABLED : 0;
		//
		//  Enable the privilege or disable all privileges.
		//
		if (AdjustTokenPrivileges(hToken, FALSE, &tp, NULL, (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL))
		{
			//
			//  Check to see if you have proper access.
			//  You may get "ERROR_NOT_ALL_ASSIGNED".
			//
			bRet = (GetLastError() == ERROR_SUCCESS);
		}
	}
	return bRet;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Error, too few arguments, expected 2, got " << argc << std::endl;
		return -1;
	}

	DWORD id = std::stoi(argv[0]);
	char exeVersion = std::stoi(argv[1]);

	std::cout << "Got: " << id << ", " << static_cast<int>(exeVersion) << std::endl;

	HANDLE mainToken;

	if (!OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, FALSE, &mainToken))
	{
		if (GetLastError() == ERROR_NO_TOKEN)
		{
			if (!ImpersonateSelf(SecurityImpersonation))
				std::cout << "Error regarding ImpersonateSelf\n";

			if (!OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, FALSE, &mainToken)) {
				std::cout << "Error opening thread token\n";
				std::cout << GetLastError();
				return 1;
			}
		}
		else
			return 1;
	}

	if (!SetPrivilege(mainToken, SE_DEBUG_NAME, true))
	{
		CloseHandle(mainToken);
		std::cout << "Couldn't set DEBUG MODE: " << GetLastError() << std::endl;
		return 1;
	};

	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, id);

	if (processHandle == NULL)
	{
		std::cout << "Error, handle was null!\n";
		std::cout << "Last error: " << GetLastError() << std::endl;
	}

	if (!InjectDLLs(processHandle, exeVersion))
		std::cout << "Error: Failed to inject dll!\n";
	else
		std::cout << "Succeded in injecting dll (" << int(exeVersion) << ")\n";
}