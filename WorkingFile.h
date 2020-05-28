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

	std::string Open(std::string path);
	std::string Save();
	std::string SaveAs(std::string path);

    std::string CreateShape(std::vector<std::string> parameters);
    std::vector<block<Shape*>>& GetShapes();
    std::string FileName();

public:
	std::string path;
    std::vector<block<std::string>> file;
    std::vector < block<Shape*>> shapes;
    int localId; // It is used for assigning an id when creating an object.

    void SplitInput(std::string& input, std::vector<std::string>& tokens, std::vector<char> delimiters);
    std::string Print(std::vector<std::string> collection);

    // The functions for handling the reading and writing to file.
    void DataExtraction(std::vector<block<std::string>>& file, std::string& path);
    void DataSaving(std::vector<block<std::string>>& file, std::string path);

    // The functions for extracting only the SVG elemnts from file and creating the objects.
    void ExtractSvg(std::vector<block<std::string>>& file, std::vector<block<std::string>>& svgElements);
    void CreateObjects(std::vector<block<std::string>>& svgElements, std::vector<block<Shape*>>& shapes);
   
    // Used to synchronize the file and shapes before writing to file.
    void SynchronizeFileAndShapes();

    bool ContainsElement(std::string& text, std::string element);
};

