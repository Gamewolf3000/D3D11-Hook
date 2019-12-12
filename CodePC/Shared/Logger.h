#pragma once

#include <fstream>
#include <string>
#include <map>

class Logger
{
	static std::map<std::string, int> counter_;
	Logger() {};
public:

	static bool log(std::string file, std::string text, bool endline = true, bool overwrite = false);

};