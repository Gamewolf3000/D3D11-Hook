#include "Processes.h"
#include "MenuOptions.h"
#include "../HookDXGI/SharedMemory.h"

#include <Windows.h>
#include <string>
#include <iostream>
#include <locale>
#include <codecvt>


std::string StatsText(unsigned int a)
{
	auto input = std::to_string(a);
	return "Number of spins: " + input + std::string("    ").substr(0, 4 - input.size());
}

static SharedMemory statsMemory(L"D3D11Stats", 10000, true);
static SharedMemory messageMemory(L"MESSAGE_MEMORY", 255, true);


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
	system("cls");
	unsigned int counter = 0;
	while (!(GetKeyState(VK_ESCAPE) & 0x8000))
	{
		std::cout << StatsText(counter) << '\r' << std::flush;
		counter++;
	}
}

void ToggleWireframe()
{
	unsigned int id = 0;
	std::cout << "State ID: ";
	std::cin >> id;
	std::string message = ("TGRS" + std::to_string(id));
	std::memcpy(messageMemory.GetPointer(), message.c_str(), message.size() + 1); // + null (\0)
}