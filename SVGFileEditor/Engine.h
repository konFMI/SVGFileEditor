#pragma once
#include "Controller.h"

class Engine
{
public:
	Engine();
	void Run();
private:
	Controller controller;
	void SplitInput(std::string& input, std::vector<std::string>& tokens, std::vector<char> delimiters);
	int StringToInt(std::string& input);
};

