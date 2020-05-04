#include <stdafx.h>
#include <tchar.h>

#include <fstream>

#include "DeviceOverride.h"
#include "DeviceContextOverride.h"
#include "SwapChainOverride.h"
#include "SharedMemory.h"

#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#pragma comment(lib, "user32.lib")

HRESULT InitiateOverride()
{
	//MessageBoxA(0, "Initiate start!", "", 0);
	while (::GetModuleHandle(_T("D3D11.DLL")) == nullptr);
	while (::GetModuleHandle(_T("DXGI.DLL")) == nullptr);

	HRESULT hr = S_OK;
	HMODULE hDXGI = GetModuleHandle(_T("DXGI.DLL")); // Get handle to the dll?
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGISwapChain1* swap_chain = nullptr;

	if (hDXGI != NULL)
	{
		CreateDXGIFactoryType pCreateDXGIFactory = reinterpret_cast<CreateDXGIFactoryType>(GetProcAddress(hDXGI, "CreateDXGIFactory")); // Fetch the adress of the factory creator?

		if (pCreateDXGIFactory)
		{
			IDXGIFactory2* pFactory;
			hr = pCreateDXGIFactory(__uuidof(IDXGIFactory2), (void**)(&pFactory)); // Use the factory creator to create a factory

			if (pFactory)
			{
				HMODULE hD3D = nullptr;

				if (hD3D = GetModuleHandle(_T("D3D11.DLL"))) // D3D11
				{
					typedef HRESULT(__stdcall *D3D11CreateDeviceType)(IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL*, UINT, UINT, ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**); // Function to create the device and the devicecontext?

					D3D11CreateDeviceType pD3D11CreateDevice = reinterpret_cast<D3D11CreateDeviceType>(GetProcAddress(hD3D, "D3D11CreateDevice")); // Get the factory adress of what we just typdefed?

					const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0 };
					D3D_FEATURE_LEVEL initiated_feature_level;
					hr = pD3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, feature_levels, 1, D3D11_SDK_VERSION, &device, &initiated_feature_level, &deviceContext); // Use the function to create the device and device context

					if (hr != S_OK)
					{
						throw("Error creating device");
					}
				}
				else
				{
					throw("Program is not D3D11");
				}

				HWND hwnd = CreateWindowW(L"STATIC", L"DXGI Window", WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, 0,
					NULL, NULL, 0); // Create the window

				DXGI_SWAP_CHAIN_DESC1 desc;
				ZeroMemory(&desc, sizeof(desc));

				RECT rcWnd;
				GetClientRect(hwnd, &rcWnd);
				desc.Width = rcWnd.right - rcWnd.left;
				desc.Height = rcWnd.bottom - rcWnd.top;
				desc.Stereo = FALSE;
				desc.Flags = 0;
				desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
				desc.SampleDesc.Count = 1;
				desc.SampleDesc.Quality = 0;

				desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				desc.BufferCount = 2;

				desc.Scaling = DXGI_SCALING_STRETCH; //this is the implicit behavior of DXGI when you call the IDXGIFactory::CreateSwapChain method.

				if (!SUCCEEDED(pFactory->CreateSwapChainForHwnd(
					device,
					hwnd,
					&desc,
					nullptr,
					nullptr,
					&swap_chain))) // Create the swap chain
				{
					throw("Unable to create swap chain");
				}

				hook_CreateDevice.Setup(reinterpret_cast<voidFunc>(GetProcAddress(hD3D, "D3D11CreateDevice")), reinterpret_cast<voidFunc>(CreateDeviceOverride));
				hook_CreateDeviceAndSwapChain.Setup(reinterpret_cast<voidFunc>(GetProcAddress(hD3D, "D3D11CreateDeviceAndSwapChain")), reinterpret_cast<voidFunc>(CreateDeviceAndSwapChainOverride));
				//raster.SetupInterface(device, 22, reinterpret_cast<voidFunc>(CreateRasterizerState));
				//MessageBoxA(0, "Done creating the override for createraster!", "", 0);

				DestroyWindow(hwnd);
			}
			else
			{
				MessageBoxA(0, "Failed to create the factory!", "", 0);
			}
		}
	}

	DeviceOverride::GetInstance()->Init(device);
	DeviceContextOverride::GetInstance()->Init(deviceContext);
	SwapChainOverride::GetInstance()->Init(swap_chain);

	//MessageBoxA(0, "Initiate done!", "", 0);

	return hr;
}

void OverrideCreateProcess()
{
	HMODULE processHandle = GetModuleHandle(L"kernel32.dll");

	auto adress = GetProcAddress(processHandle, "CreateProcessW");
	if (!adress)
	{
		auto errorMessage = "Error hooking create!\nLasterror: " + std::to_string(GetLastError());
		MessageBoxA(0, errorMessage.c_str(), "", 0);
		Sleep(1000);
		return;
	}

	hook_CreateProcessW.Setup(reinterpret_cast<voidFunc>(adress), reinterpret_cast<voidFunc>(CreateProcessWOverride));

	adress = GetProcAddress(processHandle, "FreeLibrary");
	if (!adress)
	{
		auto errorMessage = "Error hooking FreeLibrary!\nLasterror: " + std::to_string(GetLastError());
		MessageBoxA(0, errorMessage.c_str(), "", 0);
		Sleep(1000);
		return;
	}

	hook_FreeLibrary.Setup(reinterpret_cast<voidFunc>(adress), reinterpret_cast<voidFunc>(FreeLibraryOverride));
}

DWORD WINAPI prepareHookThreadFunc( LPVOID lpParam )
{
	//MessageBoxA(0, "Prepare start!", "", 0);
	OverrideCreateProcess();
	HMODULE hD3D = nullptr;

	if (hD3D = GetModuleHandle(_T("D3D11.DLL"))) // D3D11
	{
		hook_CreateDevice.Setup(reinterpret_cast<voidFunc>(GetProcAddress(hD3D, "D3D11CreateDevice")), reinterpret_cast<voidFunc>(CreateDeviceOverride));
		hook_CreateDeviceAndSwapChain.Setup(reinterpret_cast<voidFunc>(GetProcAddress(hD3D, "D3D11CreateDeviceAndSwapChain")), reinterpret_cast<voidFunc>(CreateDeviceAndSwapChainOverride));
		hook_CreateDXGIFactory.Setup(reinterpret_cast<voidFunc>(GetProcAddress(hD3D, "CreateDXGIFactory")), reinterpret_cast<voidFunc>(CreateDXGIFactoryOverride));
		hook_CreateDXGIFactory1.Setup(reinterpret_cast<voidFunc>(GetProcAddress(hD3D, "CreateDXGIFactory1")), reinterpret_cast<voidFunc>(CreateDXGIFactory1Override));
		hook_CreateDXGIFactory2.Setup(reinterpret_cast<voidFunc>(GetProcAddress(hD3D, "CreateDXGIFactory2")), reinterpret_cast<voidFunc>(CreateDXGIFactory2Override));
		InitiateOverride();
	}
	//MessageBoxA(0, "Prepare done!", "", 0);

	return 0;
}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD reason, LPVOID lpReserved)
{
	//MessageBoxA(0, "Main!", "", 0);
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
			if(true)
			{
				CreateThread( 
					NULL,                   // default security attributes
					0,                      // use default stack size  
					prepareHookThreadFunc,      // thread function name
					NULL,		            // argument to thread function 
					0,                      // use default creation flags 
					NULL);		    // returns the thread identifier
			}
		break;

		case DLL_PROCESS_DETACH:
		//case DLL_THREAD_DETACH:
			
			/*
			TerminateThread(g_networkThreadHandle, 0);

			hhPresent.Restore(true);

			hhCreateProcessW.Restore(true);
			hhCreateProcessA.Restore(true);
			hhGetPhysicalCursorPos.Restore(true);
			hhGetCursorPos.Restore(true);
			hhSetCursorPos.Restore(true);
			hhWindowFromPoint.Restore(true);
			hhChildWindowFromPoint.Restore(true);
			hhDefWindowProcW.Restore(true);
			hhGetCursorInfo.Restore(true);
			hhGetWindowPlacement.Restore(true);
			hhScreenToClient.Restore(true);
			hhGetFocus.Restore(true);
			hhGetForegroundWindow.Restore(true);

			MessageBoxA(0, "DETACH", "LOL", 0);
			*/

		break;

		case DLL_THREAD_ATTACH:
			{

			}
		break;
	}

	return(true);
}