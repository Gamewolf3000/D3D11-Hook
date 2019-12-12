#pragma once

#include <Windows.h>

void StartInjecter(DWORD processID, char exeVersion);

bool StartProcess(const wchar_t* applicationName);

void InjectThreadFunction();