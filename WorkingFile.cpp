#include "WorkingFile.h"

WorkingFile::WorkingFile()
{
}

std::string WorkingFile::Open(std::string path)
{
	std::string message = "";
	return message;
}

void WorkingFile::Save()
{
}
void WorkingFile::SaveAs(std::string newPath)
{
}

Repository<Shape>* WorkingFile::GetShapes()
{
	return &shapes;
}
