#include "Controller.h"
#include"Repository.h"


Controller::Controller()
{
	currentFile = NULL;
}

string Controller::Open(string path)
{
	WorkingFile workingFile;
	std::string message = workingFile.Open(path);
	file.Create(&workingFile);
	currentFile = &workingFile;
	return string();
}

string Controller::Close()
{
	return string();
}

string Controller::Save()
{

	return "";
}

string Controller::SaveAs(string)
{
	return string();
}

string Controller::Help()
{
	return string();
}

void Controller::Exit()
{
	return;
}

string Controller::Print()
{
	return string();
}

string Controller::Create(std::vector<std::string> tokens)
{
	return string();
}

string Controller::Erase(int)
{
	return string();
}

string Controller::Translate(int, int,int)
{
	return string();
}

string Controller::Within(std::vector<string>&)
{
	return string();
}
