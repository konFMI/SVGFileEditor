#include "WorkingFile.h"

WorkingFile::WorkingFile()
{
    path = "";
    file.clear();
    shapes.clear();
    localId = 100;
}

std::string WorkingFile::Open(std::string path)
{
    localId = 100; 
    this->path = path;
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

std::string WorkingFile::CreateShape(std::vector<std::string> parameters)
{
    Shape* shape = NULL;
    std::string shapeName = parameters[0];
    if (shapeName == "rectangle" && parameters.size() == 6)
    {
        int x = 0, y = 0, width = 0, height = 0;
        std::string fill = "";
        if (StringToInt(parameters[1], x) && StringToInt(parameters[2], y) && StringToInt(parameters[3], width) && StringToInt(parameters[4], height))
        {
            fill = parameters[5];
            shape = new Rectangle("rectangle", x, y, width, height, fill);
            shapes.push_back({ std::vector<Shape*>{shape}, localId++ });
        }
    }
    else if (parameters[0] == "circle" && parameters.size() == 5)
    {
        int cx = 0, cy = 0, r = 0;
        std::string fill = "";
        if (StringToInt(parameters[1], cx) && StringToInt(parameters[2], cy) && StringToInt(parameters[3], r))
        {
            fill = parameters[4];
            shape = new Circle("circle", cx, cy, r, fill);
            shapes.push_back({ std::vector<Shape*>{shape}, localId++ });
        }
    }
    else
    {
        throw std::string("Not supported shape.");
    }
    
    return "Successfully created a " + parameters[0];
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

void WorkingFile::DataExtraction(std::vector<block<std::string>>& file, std::string& path)
{
    std::ifstream svgFile(path);

    if (svgFile.is_open())
    {
        std::string line;
        std::vector<std::string> svgPart, notSvgLines;
        int fileLocation = 0;

        while (std::getline(svgFile, line))
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
                        file.push_back({ std::vector<std::string>{"NOTSVGSTART"},-1 });
                        file.push_back({ notSvgLines,fileLocation });
                        fileLocation++;
                        file.push_back({ std::vector<std::string>{"NOTSVGEND"},-1 });
                        notSvgLines.clear();
                    }
                    while (getline(svgFile, line))
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
                        file.push_back({ std::vector<std::string>{"SVGSTART"},-1 });
                        file.push_back({ svgPart,fileLocation });
                        fileLocation++;
                        file.push_back({ std::vector<std::string>{"SVGEND"},-1 });
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

        svgFile.close();
    }
    else
    {
        //throw std::string("Unable to open file.");
    }

    return;
}
void WorkingFile::DataSaving(std::vector<block<std::string>>& file, std::string path)
{
    std::ofstream svgFile(path, std::ios::trunc);

    if (svgFile.is_open())
    {
        for (size_t i = 0; i < file.size(); i++)
        {
            if (file[i].id == -1 && file[i].data[0] == "SVGSTART" && (i + 2) < file.size())
            {
                i += 1;
                svgFile << "<svg>\n";
                svgFile << Print(file[i].data);
            }
            else if (file[i].id == -1 && file[i].data[0] == "SVGEND")
            {
                svgFile << "</svg>\n";
            }
            else if (file[i].id == -1 && file[i].data[0] == "NOTSVGSTART" && (i + 2) < file.size())
            {
                i += 1;
                svgFile << Print(file[i].data);
            }
        }
        svgFile.close();
    }
}

void WorkingFile::ExtractSvg(std::vector<block<std::string>>& file, std::vector<block<std::string>>& svgElements)
{
    for (size_t i = 0; i < file.size(); i++)
    {
        if (file[i].id == -1 && file[i].data[0] == "SVGSTART" && (i + 1) < file.size())
        {
            i++;
            block<std::string> data = file[i];
            svgElements.push_back(data);
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
    int counter = 0;
    for (size_t i = 0; i < shapes.size(); i++)
    {
        counter = shapes[i].id;
        size_t j = 0;
        std::vector<std::string> data;
        for (size_t k = 0; k < shapes[i].data.size(); k++)
        {
            data.push_back(shapes[i].data[k]->ToStringFile());
        }
        while (j < file.size() && file[j].id != counter)
        {
            j++;
        }
        if (file[j].id == counter)
        {
            file[j].data.clear();
            
            file[j].data = data;
        }
        else
        {
            size_t lastSVGTagIndex = 0;
            for (size_t k = 0; i < file.size(); i++)
            {
                if (file[k].data.size() == 1 && file[k].data[0] == "SVGSTART")
                {
                    lastSVGTagIndex = k+2;
                }
            }
           
            file.push_back({ std::vector<std::string>{},0 });
            for (size_t k = file.size()-1; k > lastSVGTagIndex; k--)
            {
                file[k] = file[k - 1];
            }
            file[lastSVGTagIndex + 1].data = data;
            file[lastSVGTagIndex + 1].id = counter;

        }
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
bool StringToInt(std::string& strInt, int& integer)
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