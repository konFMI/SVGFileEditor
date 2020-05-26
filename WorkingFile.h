#pragma once
#include <string>
#include"Shape.h"
#include"Repository.h"
class WorkingFile
{
public:
	WorkingFile();
	std::string Open(std::string);
	void Save();
	void SaveAs(std::string);

	Repository<Shape>* GetShapes();
private:
	std::string path;
	Repository<Shape> shapes;

};

