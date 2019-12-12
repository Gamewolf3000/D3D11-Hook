#pragma once

#include <Windows.h>

#include <locale>
#include <codecvt>
#include <string>
#include <iostream>
#include <tlhelp32.h>
#include <cstdio>
#include "../../Shared/DLLUtils.h"
#include "../HookDXGI/SharedMemory.h"



bool InjectDLLs(HANDLE hProcess, char exeVersion)
{
	bool result = false;

	if (exeVersion == 32) // 32 bit binary
	{
#ifdef _DEBUG

		result = InjectDLL(
			hProcess,
			"HookDXGI32D.dll");

#else

		result = InjectDLL(
			hProcess,
			"HookDXGI32.dll");

#endif
	}
	else if (exeVersion == 64)
	{
#ifdef _DEBUG

		result = InjectDLL(
			hProcess,
			"HookDXGI64D.dll");

#else

		result = InjectDLL(
			hProcess,
			"HookDXGI64.dll");

#endif
	}
	else
	{
		std::cout << "Error: Unknown exe type (" << int(exeVersion) << ")\n";
	}
	return result;
}