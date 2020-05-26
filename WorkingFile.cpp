#include "WorkingFile.h"

WorkingFile::WorkingFile()
{
    path = "";
    file.clear();
    shapes.clear();
}
std::string WorkingFile::Open(std::string path)
{
	std::string message ="\"" + path + "\" has been opened.";
    DataExtraction(file, path);
    std::vector<block<std::string>> svgElements;
    ExtractSvg(file, svgElements);
    CreateObjects(svgElements, shapes);
	return message;
}
std::string WorkingFile::Save()
{
    SynchronizeFileAndShapes();
    DataSaving(file, path);
    return "Successfully  save \"" + path + "\"";
}
std::string WorkingFile::SaveAs(std::string newPath)
{
    SynchronizeFileAndShapes();
    DataSaving(file, newPath);

    return "Successfully saved \"" + newPath + "\"";
}
std::vector<block<Shape*>>& WorkingFile::GetShapes()
{
    return shapes;
}
std::string WorkingFile::FileName()
{
    return path;
}
void WorkingFile::SplitInput(std::string& input, std::vector<std::string>& tokens, std::vector<char> delimiters)
{
    char* memblock = &*input.begin();
    std::string temp = "";

    for (size_t i = 0; i < input.length(); i++)
    {
        bool condition = false;
        for (size_t j = 0; j < delimiters.size(); j++)
        {

            condition = condition || (memblock[i] == delimiters[j]);

        }
        if (condition)
        {
            if (temp != "")
            {
                tokens.push_back(temp);
                temp = "";
            }
        }
        else
        {
            temp += memblock[i];
        }

    }
    if (temp != "")
    {
        tokens.push_back(temp);
    }
}
bool WorkingFile::StringToInt(std::string& strInt, int& integer)
{
    char* memblock = &*strInt.begin();
    int number = 0;
    for (size_t i = 0; i < strInt.length(); i++)
    {
        if (isdigit(memblock[i]))
        {
            number *= 10;
            number += (memblock[i] - '0');
        }
        else
        {
            return false;
        }
    }
    integer = number;
    return true;
}
std::string WorkingFile::Print(std::vector<std::string> collection)
{
    {
        std::string output = "";
        for (size_t i = 0; i < collection.size(); i++)
        {
            output += collection[i];
            output += "\n";
        }
        return output;
    }
}
bool WorkingFile::ContainsElement(std::string& text, std::string element)
{
    bool contains = false;

    if (text.length() > 0)
    {
        char* memblock = &*text.begin();
        for (size_t i = 0; i < text.length() - element.length() + 1; i++)
        {
            for (size_t j = 0; j < element.length(); j++)
            {
                if (memblock[i + j] == element[j])
                {
                    contains = true;
                }
                else
                {
                    contains = false;
                    break;
                }
            }
            if (contains)
            {
                break;
            }
        }
    }
    return contains;
}
void WorkingFile::DataExtraction(std::vector<block<std::string>>& fileLines, std::string& path)
{
    std::ifstream file(path);

    if (file.is_open())
    {
        std::string line;
        std::vector<std::string> svgPart, notSvgLines;
        int fileLocation = 0;

        while (std::getline(file, line))
        {
            bool svgOpenTag = false;
            bool svgCloseTag = false;

            if (line.length() > 0)
            {
                svgOpenTag = ContainsElement(line, "<svg>");
                svgCloseTag = ContainsElement(line, "</svg>");
                if (svgOpenTag && !svgCloseTag)
                {
                    if (!notSvgLines.empty())
                    {
                        fileLines.push_back({ std::vector<std::string>{"NOTSVGSTART"},-1 });
                        fileLines.push_back({ notSvgLines,fileLocation });
                        fileLocation++;
                        fileLines.push_back({ std::vector<std::string>{"NOTSVGEND"},-1 });
                        notSvgLines.clear();
                    }
                    while (getline(file, line))
                    {
                        svgCloseTag = ContainsElement(line, "</svg>");
                        if (svgCloseTag)
                        {
                            break;
                        }
                        else
                        {
                            svgPart.push_back(line);
                        }
                    }

                    if (!svgCloseTag)
                    {
                        throw std::string("Format error.");
                    }

                    if (!svgPart.empty())
                    {
                        fileLines.push_back({ std::vector<std::string>{"SVGSTART"},-1 });
                        fileLines.push_back({ svgPart,fileLocation });
                        fileLocation++;
                        fileLines.push_back({ std::vector<std::string>{"SVGEND"},-1 });
                        svgPart.clear();
                    }
                }
                else if (svgCloseTag)
                {
                    throw std::string("Format error.");
                }
                else
                {
                    notSvgLines.push_back(line);
                }
            }
        }

        file.close();
    }
    else
    {
        throw std::string("Unable to open file.");
    }

    return;
}
void WorkingFile::DataSaving(std::vector<block<std::string>>& fileLines, std::string path)
{
    std::ofstream file(path, std::ios::trunc);

    if (file.is_open())
    {
        for (size_t i = 0; i < fileLines.size(); i++)
        {
            if (fileLines[i].id == -1 && fileLines[i].data[0] == "SVGSTART" && (i + 2) < fileLines.size())
            {
                i += 1;
                file << "<svg>\n";
                file << Print(fileLines[i].data);
            }
            else if (fileLines[i].id == -1 && fileLines[i].data[0] == "SVGEND")
            {
                file << "</svg>\n";
            }
            else if (fileLines[i].id == -1 && fileLines[i].data[0] == "NOTSVGSTART" && (i + 2) < fileLines.size())
            {
                i += 1;
                file << Print(fileLines[i].data);
            }
        }
        file.close();
    }
}
void WorkingFile::ExtractSvg(std::vector<block<std::string>>& source, std::vector<block<std::string>>& svg)
{
    for (size_t i = 0; i < source.size(); i++)
    {
        if (source[i].id == -1 && source[i].data[0] == "SVGSTART" && (i + 1) < source.size())
        {
            i++;
            block<std::string> data = source[i];
            svg.push_back(data);
        }
    }
}
void WorkingFile::CreateObjects(std::vector<block<std::string>>& svgElements, std::vector<block<Shape*>>& objects)
{
    std::vector<std::string> tokens;
    std::vector<Shape*> shapes;

    Shape* shape = NULL;
    for (size_t i = 0; i < svgElements.size(); i++)
    {
        shapes.clear();
        int blockId = svgElements[i].id;
        for (size_t j = 0; j < svgElements[i].data.size(); j++)
        {
            tokens.clear();
            if (!svgElements[i].data[j].empty())
            {
                SplitInput(svgElements[i].data[j], tokens, std::vector<char>{' ', '<', '>', '/', '=', '\"'});
                if (tokens[0] == "rect")
                {
                    int x = 0, y = 0, width = 0, height = 0;
                    std::string fill = "";
                    if (tokens.size() == 11 && StringToInt(tokens[2], x) && StringToInt(tokens[4], y) && StringToInt(tokens[6], width) && StringToInt(tokens[8], height))
                    {
                        fill = tokens[10];
                        shape = new Rectangle("rectangle", x, y, width, height, fill);
                        shapes.push_back(shape);
                    }
                }
                else if (tokens[0] == "circle")
                {
                    int cx = 0, cy = 0, r = 0;
                    std::string fill = "";
                    if (StringToInt(tokens[2], cx) && StringToInt(tokens[4], cy) && StringToInt(tokens[6], r))
                    {
                        fill = tokens[8];
                        shape = new Circle("circle", cx, cy, r, fill);
                        shapes.push_back(shape);
                    }
                }
            }

        }
        objects.push_back({ shapes,svgElements[i].id });
    }
}

void WorkingFile::SynchronizeFileAndShapes()
{
}

