#pragma once
#include <string>
#include"Shape.h"
#include"Repository.h"
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
	string Translate(int, int,int=-1);
	string Within(std::vector<std::string>&);
private:
	WorkingFile* currentFile;
	Repository<WorkingFile> file;
};
