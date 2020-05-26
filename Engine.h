#pragma once
#include "Controller.h"
class Engine
{
public:
	Engine();
	void Run();
private:
	Controller controller;
	void SplitInput(std::string&, std::vector<std::string>&, std::vector<char>);
	int StringToInt(std::string& width);
};

