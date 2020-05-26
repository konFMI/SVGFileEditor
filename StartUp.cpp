#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include"Repository.h"
#include "Engine.h"
#include "StartUp.h"

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ofstream;
using std::ifstream;
using std::for_each;

struct block
{
    vector<string> data;
    int location;
};
//void SplitInput(std::string& input, std::vector<std::string>& tokens, std::vector<char> delimiters)
//{
//    char* memblock = &*input.begin();
//    std::string temp = "";
//
//    for (size_t i = 0; i < input.length(); i++)
//    {
//        bool condition = false;
//        
//        if (condition)
//        {
//            if (temp != "")
//            {
//                tokens.push_back(temp);
//                temp = "";
//            }
//        }
//        else
//        {
//            temp += memblock[i];
//        }
//
//    }
//    if (temp != "")
//    {
//        tokens.push_back(temp);
//    }
//}

string Print(std::vector<std::string> collection)
{
    std::string output = "";
    for (size_t i = 0; i < collection.size() ; i++)
    {
        output += collection[i];
        output += "\n";
    }
    return output;
}
bool ContainsElement(string& text, string element)
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
void DataExtraction(vector<vector<string>>& fileLines, string& path)
{
    ifstream file(path);
    if (file.is_open())
    {
        string line;
        vector<string> svgPart, notSvgLines;
        int fileLocation = 0;
        int svgOpenTagsCounter = 0;
        int svgCloseTagsCounter = 0;

        while (getline(file, line))
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
                        fileLines.push_back(vector<string>{"NOTSVGSTART"});
                        fileLines.push_back(vector<string>{std::to_string(fileLocation)});
                        fileLocation++;
                        fileLines.push_back(notSvgLines);
                        fileLines.push_back(vector<string>{"NOTSVGEND"});
                        notSvgLines.clear();
                    }
                    svgCloseTagsCounter++;
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
                        fileLines.push_back(vector<string>{"SVGSTART"});
                        fileLines.push_back(vector<string>{std::to_string(fileLocation)});
                        fileLocation++;
                        fileLines.push_back(svgPart);
                        fileLines.push_back(vector<string>{"SVGEND"});
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
        cout << "Unable to open file." << endl;
    }

    return;
}
void DataSaving(vector<vector<string>>& fileLines, string path)
{
    ofstream file(path, std::ios::trunc);

    if (file.is_open())
    {
        for (size_t i = 0; i < fileLines.size(); i++)
        {
            if (fileLines[i].size() == 1 && fileLines[i][0] == "SVGSTART" && (i+2) < fileLines.size())
            {
                i += 2;
                file << "<svg>\n";
                file << Print(fileLines[i]);
                
            }
            else if (fileLines[i].size() == 1 && fileLines[i][0] == "SVGEND")
            {
                file << "</svg>\n";
            }
            else if (fileLines[i].size() == 1 && fileLines[i][0] == "NOTSVGSTART" && (i + 2) < fileLines.size())
            {
                i += 2;
                file << Print(fileLines[i]);

            }
            
        }
        file.close();
    }


}
void ExtractSvg(vector<vector<string>>& source, vector<block>& svg)
{
    for (size_t i = 0; i < source.size(); i++)
    {
        if (source[i].size() == 1 && source[i][0] == "SVGSTART" && (i+2) < source.size())
        {
            i++;

            int position;
            try {
                position = stoi(source[i][0]);
            }
            catch (const std::invalid_argument& ia) {
                std::cout << "Invalid argument." << ia.what() << '\n';
            }
            i++;
            block data = { source[i],position };
            svg.push_back(data);


        }
    }
}
int main()
{
    //Engine engine;
    //engine.Run();
    vector<vector<string>> file;
    vector<block> svg;
    string path = "./WorkingFiles/figures.svg";
    try
    {
        DataExtraction(file,path);
    }
    catch (std::string ms)
    {
        cout << ms << endl;
    }
    ExtractSvg(file, svg);

    for (size_t i = 0; i < svg.size(); i++)
    {
        cout << "Location: " << svg[i].location << endl;
        cout << Print(svg[i].data);
    }


    
	return 0;
}