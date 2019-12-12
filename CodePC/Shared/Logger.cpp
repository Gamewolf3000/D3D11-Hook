#include "Logger.h"

std::map<std::string, int> Logger::counter_;

bool Logger::log(std::string file, std::string text, bool endline, bool overwrite)
{
	//return false;
	std::ofstream outfile;

	if (counter_[file] == 0 && overwrite)
	{
		outfile.open(file, std::ios_base::out);
	}
	else
	{
		outfile.open(file, std::ios_base::app);
	}

	if (outfile.is_open())
	{
		counter_[file]++;

		outfile << text;
		
		if (endline)
			outfile << std::endl;

		outfile.close();

		return true;
	}

	return false;
}