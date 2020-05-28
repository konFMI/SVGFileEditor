#pragma once
#include <string>
#include"Shape.h"
#include"WorkingFile.h"

using std::string;

class Controller
{
public:
	Controller();

	string Open(string);
	string Close();
	string Save();
	string SaveAs(string);
	string Help();
	void Exit();

	string Print();
	string Create(std::vector<std::string>);
	string Erase(int);

	string Within(std::vector<std::string>&);
	string Translate(std::vector<std::string> tokens);
private:
	WorkingFile* currentFile;
	std::vector<WorkingFile> files;

	string Translate(int, int,int=-1);

	void SplitInput(std::string& input, std::vector<std::string>& tokens, std::vector<char> delimiters);
	
};

