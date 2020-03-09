#include "Processes.h"
#include "MenuOptions.h"
#include "../HookDXGI/SharedMemory.h"
#include "../../Shared/SharedData.h"

#include <Windows.h>
#include <string>
#include <iostream>
#include <locale>
#include <codecvt>
#include <thread>

static HANDLE statsMutex;
static SharedMemory statsMemory(L"D3D11Stats", sizeof(PerFrameBuffer), true);
static SharedMemory messageMemory(L"MESSAGE_MEMORY", 255, true);

void InitStatsMemory()
{
	statsMutex = CreateMutexA(NULL, false, "statsMutex");
	if (statsMutex == NULL)
		std::cout << "Error creating stats mutex, GetLastError: " << GetLastError() << std::endl;

	PerFrameBuffer* buffer = static_cast<PerFrameBuffer*>(statsMemory.GetPointer());
	*buffer = PerFrameBuffer();
}

std::string StatsText()
{

	PerFrameBuffer* buffer = static_cast<PerFrameBuffer*>(statsMemory.GetPointer());
	PerFrameStats stats;
	
	DWORD dwWaitResult = WaitForSingleObject(statsMutex, INFINITE);
	buffer->nextToWriteTo = 1 - buffer->nextToWriteTo;
	if(!ReleaseMutex(statsMutex))
		std::cout << "Error when releasing mutex, GetLastError: " << GetLastError() << std::endl;
	stats = buffer->stats[1 - buffer->nextToWriteTo];


	std::string toReturn = "Draw calls: " + std::to_string(stats.nrOfDrawCalls) + '\n';
	toReturn += "DrawIndexed calls: " + std::to_string(stats.nrOfDrawIndexedCalls) + '\n';
	toReturn += "VertexShaders used: " + std::to_string(stats.nrOfVertexShadersUsed) + '\n';
	toReturn += "RasterizerStates used: " + std::to_string(stats.nrOfRasterizerStates) + '\n';

	return toReturn;
}

void InjectIntoProgram()
{
	std::string input;
	std::getline(std::cin, input);
	
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring applicationName = converter.from_bytes(input.c_str());
	auto indexOfLastSlash = applicationName.find_last_of(L"\\");
	auto processWorkingDirectory = applicationName.substr(0, indexOfLastSlash);

	if (!StartProcess(applicationName.c_str()))
	{
		std::cout << "Error starting application!\n";
	}
}

void DisplayStats()
{
	using namespace std::chrono_literals;
	while (!(GetKeyState(VK_ESCAPE) & 0x8000))
	{
		PerFrameBuffer* buffer = static_cast<PerFrameBuffer*>(statsMemory.GetPointer());

		system("cls");
		std::cout << StatsText() << '\r' << std::flush;
		std::this_thread::sleep_for(0.2s);
	}
}

void ToggleWireframe()
{
	std::string id;
	std::cout << "State ID: ";
	std::getline(std::cin, id);
	std::string message = ("TGRS" + id);
	std::memcpy(messageMemory.GetPointer(), message.c_str(), message.size() + 1); // + null (\0)
}