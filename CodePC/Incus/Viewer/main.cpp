#include "MenuOptions.h"
#include "Processes.h"

#include <string>
#include <iostream>
#include <thread>

void PrintMenu()
{
	std::cout << "Available choices\n";
	std::cout << "1: Inject into exe\n";
	std::cout << "2: Display stats\n";
	std::cout << "3: Toggle wireframe\n";
}

int main(int argc, char** argv)
{
	std::thread thread(InjectThreadFunction);

	std::string input = "";
	while (input != "exit" && input != "quit")
	{
		PrintMenu();
		std::getline(std::cin, input);

		if (input == "1")
		{
			InjectIntoProgram();
		}
		else if (input == "2")
		{
			DisplayStats();
		}
		else if (input == "3")
		{
			ToggleWireframe();
		}
	}
}