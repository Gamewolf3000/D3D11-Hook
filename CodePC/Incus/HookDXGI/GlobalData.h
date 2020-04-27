#pragma once

#include <d3d11_4.h>
#include <dxgi1_6.h>
#include "D3DResolve.h"
#include "HardHook.h"
#include <tchar.h>
#include <unordered_map>
#include "../../Shared/DLLUtils.h"
#include "JobHandler.h"
#include "SharedMemory.h"
#include "../../Shared/SharedData.h"
#include <FakeID3D11Device.hpp>


#include <locale>
#include <codecvt>
#include <string>
#include <Windows.h>

struct StoredResource
{
	ID3D11Resource* originalResource;
	ID3D11Resource* replacementResource;
	ID3D11Resource* sharedResource;
	HANDLE resourceHandle;
};

static JobHandler jobHandler(false);
static std::unordered_map<ID3D11Resource*, StoredResource> storedResources;
static HardHook hook_CreateProcessW;
static HardHook hook_FreeLibrary;
static HardHook hook_CreateDevice;
static HardHook hook_CreateDeviceAndSwapChain;
static ID3D11Device* GlobalDevice = nullptr;
static ID3D11DeviceContext* GlobalDeviceContext = nullptr;
static HANDLE statsMutex = OpenMutexA(SYNCHRONIZE, false, "statsMutex");
static SharedMemory statsMemory(L"D3D11Stats", sizeof(PerFrameBuffer), false);
static SharedMemory injectMemory(L"INJECTOR_MEMORY", sizeof(bool) + sizeof(DWORD) + sizeof(char), false);
static SharedMemory messageMemory(L"MESSAGE_MEMORY", 255, false);
static PerFrameStats perFrameStats;

struct RasterizerStateData
{
	ID3D11RasterizerState* original;
	ID3D11RasterizerState* wireframe;
	bool useWireframe = false;
};

static std::vector<RasterizerStateData> rData;

#if _WIN64
static HMODULE myHandle = GetModuleHandle(L"HookDXGI64.dll");
#else
static HMODULE myHandle = GetModuleHandle(L"HookDXGI32.dll");
#endif


HANDLE sharedMutex = OpenMutexA(SYNCHRONIZE, false, "D3D11SHAREDMUTEX");

char DetermineExecutableVersion(LPCWSTR applicationName)
{
	//MessageBoxW(0, applicationName, L"DetermineExecutableVersion", 0);
	DWORD binaryType;
	BOOL result = GetBinaryTypeW(applicationName, &binaryType);

	if (binaryType == SCS_32BIT_BINARY) // 32 bit binary
		return 32;
	else if (binaryType == SCS_64BIT_BINARY)
		return 64;
	else
	{
		//std::wstring message = L"Application ";
		//message += applicationName;
		//message += L" was of unknown exe type, GetBinaryType gave: ";
		//message += std::to_wstring(binaryType);
		if (!result)
		{
			//DWORD lastError = GetLastError();
			//if(lastError == 123 && applicationName == NULL)
				//MessageBoxW(0, L"THE BASTARD NAME IS NULL", L"DetermineExecutableVersion", 0);
		}
		return static_cast<char>(binaryType);
	}
}

char DetermineExecutableVersion(LPCSTR applicationName)
{
	DWORD binaryType;
	GetBinaryTypeA(applicationName, &binaryType);

	if (binaryType == SCS_32BIT_BINARY) // 32 bit binary
		return 32;
	else if (binaryType == SCS_64BIT_BINARY)
		return 64;
	else
	{
		//std::string message = "Application ";
		//message += applicationName;
		//message += " was of unknown exe type, GetBinaryType gave: ";
		//message += std::to_string(binaryType);
		//MessageBoxA(0, message.c_str(), "", 0);
		return static_cast<char>(binaryType);
	}
}

BOOL WINAPI FreeLibraryOverride(HMODULE hLibModule)
{

	if(myHandle == NULL)
		MessageBoxW(0, L"Failed to get my own handle...", L"", 0);
	
	if (hLibModule == myHandle)
	{
		MessageBoxW(0, L"Oh snap they trying to kick me out!", L"", 0);
		return true;
	}
	else
	{
		hook_FreeLibrary.Restore();
		BOOL result = FreeLibrary(hLibModule);
		//if(result)
		//	MessageBoxW(0, L"FreeLibrary function succeded!", L"", 0);
		//else
		//	MessageBoxW(0, L"FreeLibrary function failed!", L"", 0);
		hook_FreeLibrary.Inject();
		return result;
	}

	//hook_FreeLibrary.Restore();
	//BOOL result = FreeLibrary(hLibModule);
	//hook_FreeLibrary.Inject();
	//return result;

	//return true;
}

BOOL WINAPI CreateProcessWOverride(
	LPCWSTR               lpApplicationName,
	LPWSTR                lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL                  bInheritHandles,
	DWORD                 dwCreationFlags,
	LPVOID                lpEnvironment,
	LPCWSTR               lpCurrentDirectory,
	LPSTARTUPINFOW        lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
)
{
	//std::wstring message = L"Called my create process (W): ";
	//message += lpApplicationName;
	//MessageBoxW(0, message.c_str(), L"", 0);

	hook_CreateProcessW.Restore();
	BOOL result = CreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles,
		dwCreationFlags | CREATE_SUSPENDED, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);

	if (result)
	{
		while (reinterpret_cast<bool*>(injectMemory.GetPointer())[0] == true)
		{
			// SPIN LOCK
			// Waiting for potential previous exe that was launched
		}

		std::memcpy(static_cast<char*>(injectMemory.GetPointer()) + sizeof(bool), &lpProcessInformation->dwProcessId, sizeof(DWORD));
		char exeVersion;

		if (lpApplicationName == NULL)
		{
			if(lpCommandLine == NULL)
				MessageBoxW(0, L"Well now you are just messing with me...", L"CreateProcessWApplicationNameWasNull", 0);
			else if(lpCommandLine[0] == '\"')
			{
				//MessageBoxW(0, L"\" case which I have not dealt with yet", L"CreateProcessWApplicationNameWasNull", 0);
				std::wstring nameFromCommand(lpCommandLine + 1);
				nameFromCommand = nameFromCommand.substr(0, nameFromCommand.find_first_of('"'));
				exeVersion = DetermineExecutableVersion(nameFromCommand.c_str());
			}
			else
			{
				std::wstring nameFromCommand(lpCommandLine);
				nameFromCommand = nameFromCommand.substr(0, nameFromCommand.find_first_of(' '));
				exeVersion = DetermineExecutableVersion(nameFromCommand.c_str());
				//MessageBoxW(0, nameFromCommand.c_str(), L"CreateProcessWApplicationNameWasNull", 0);
			}

		}
		else
		{
			exeVersion = DetermineExecutableVersion(lpApplicationName);
		}

		std::memcpy(static_cast<bool*>(injectMemory.GetPointer()) + sizeof(bool) + sizeof(DWORD), &exeVersion, sizeof(char));
		static_cast<bool*>(injectMemory.GetPointer())[0] = true;


		//nu är vi nog redo att låta processen köra igång igen
		Sleep(1000);

		ResumeThread((*lpProcessInformation).hThread);
	}
	else
	{
		MessageBoxA(0, "Failed to create process (W)", "", 0);
	}

	hook_CreateProcessW.Inject();
	//MessageBoxA(0, "End of (W)", "", 0);

	return result;
}

HRESULT WINAPI CreateDeviceOverride(
	IDXGIAdapter            *pAdapter,
	D3D_DRIVER_TYPE         DriverType,
	HMODULE                 Software,
	UINT                    Flags,
	const D3D_FEATURE_LEVEL *pFeatureLevels,
	UINT                    FeatureLevels,
	UINT                    SDKVersion,
	ID3D11Device            **ppDevice,
	D3D_FEATURE_LEVEL       *pFeatureLevel,
	ID3D11DeviceContext     **ppImmediateContext)
{
	bool startedNull = (ppDevice == NULL || ppImmediateContext == NULL);
	//MessageBoxA(0, "CreateDevice called!", "", 0);
	hook_CreateDevice.Restore();
	HRESULT hr = D3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
	GlobalDevice = *ppDevice;
	GlobalDeviceContext = *ppImmediateContext;
	FakeID3D11Device* test = nullptr;
	if (hr == S_OK && startedNull != true && ppDevice != nullptr && ppDevice != NULL && *ppDevice != nullptr && *ppDevice != nullptr)
	{
		test = new FakeID3D11Device(*ppDevice);
		*ppDevice = test;
		//MessageBoxA(0, "We created a fake device!", "", 0);
	}
	//*ppDevice = test;
	hook_CreateDevice.Inject();

	return hr;
}

HRESULT WINAPI CreateDeviceAndSwapChainOverride(
	IDXGIAdapter               *pAdapter,
	D3D_DRIVER_TYPE            DriverType,
	HMODULE                    Software,
	UINT                       Flags,
	const D3D_FEATURE_LEVEL    *pFeatureLevels,
	UINT                       FeatureLevels,
	UINT                       SDKVersion,
	const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
	IDXGISwapChain             **ppSwapChain,
	ID3D11Device               **ppDevice,
	D3D_FEATURE_LEVEL          *pFeatureLevel,
	ID3D11DeviceContext        **ppImmediateContext
)
{
	bool startedNull = (ppDevice == NULL || ppImmediateContext == NULL);
	//MessageBoxA(0, "CreateDeviceAndSwapChain called!", "", 0);
	hook_CreateDeviceAndSwapChain.Restore();
	//Flags |= D3D11_CREATE_DEVICE_DEBUG;
	//DriverType = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE;
	HRESULT hr = D3D11CreateDeviceAndSwapChain(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
	GlobalDevice = *ppDevice;
	GlobalDeviceContext = *ppImmediateContext;
	FakeID3D11Device* test = nullptr;
	if (hr == S_OK && startedNull != true && ppDevice != nullptr && ppDevice != NULL && *ppDevice != nullptr && *ppDevice != nullptr)
	{
		test = new FakeID3D11Device(*ppDevice);
		*ppDevice = test;
		//MessageBoxA(0, "We created a fake device!", "", 0);
	}
	hook_CreateDeviceAndSwapChain.Inject();
	return hr;
}