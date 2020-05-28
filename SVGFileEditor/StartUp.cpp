#include "Engine.h"
#include<iostream>
#include"WorkingFile.h"
#include<vector>
using std::vector;
using std::string;
using std::cout;
using std::endl;

int main()
{
    //Engine engine;
    //engine.Run();
    WorkingFile workingFile;
    std::vector<block<std::string>> file, svg;
    string path = "./WorkingFiles/figures.svg";
    workingFile.DataExtraction(file, path);
    for (size_t i = 0; i < file.size(); i++)
    {
        for (size_t j = 0; j < file[i].data.size(); j++)
        {
            
            cout << file[i].data[j] << endl;
            
        }
        cout << file[i].id << endl;
    }


  
	return 0;
}