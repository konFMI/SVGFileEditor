#pragma once
#include <string>
#include <vector>
#include<fstream>
#include "Shape.h"
#include"Rectangle.h"
#include"Circle.h"

template<class T>
struct block
{
	std::vector<T> data;
	int id;
};
bool StringToInt(std::string& strInt, int& integer);
class WorkingFile
{
public:
	WorkingFile();
    std::string CreateShape(std::vector<std::string> parameters);
	std::string Open(std::string);
	std::string Save();
	std::string SaveAs(std::string);
    std::vector<block<Shape*>>& GetShapes();
    std::string FileName();

	
private:
	std::string path;
    std::vector<block<std::string>> file;
    std::vector < block<Shape*>> shapes;
    int localId;

    void SplitInput(std::string& input, std::vector<std::string>& tokens, std::vector<char> delimiters);
    std::string Print(std::vector<std::string> collection);
    bool ContainsElement(std::string& text, std::string element);
    void DataExtraction(std::vector<block<std::string>>& fileLines, std::string& path);
    void DataSaving(std::vector<block<std::string>>& fileLines, std::string path);
    void ExtractSvg(std::vector<block<std::string>>& source, std::vector<block<std::string>>& svg);
    void CreateObjects(std::vector<block<std::string>>& svgElements, std::vector<block<Shape*>>& objects);
    void SynchronizeFileAndShapes();
};

