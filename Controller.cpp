#include "Controller.h"
#include"Repository.h"


Controller::Controller()
{
	currentFile = NULL;
}

string Controller::Open(string path)
{
	WorkingFile* workingFile = new WorkingFile();
	std::string message = workingFile->Open(path);
	files.push_back(*workingFile);
	currentFile = workingFile;
	return message;
}

string Controller::Close()
{
	string message = "Closed \"" + currentFile ->FileName() + "\"";
	return message;
}

string Controller::Save()
{
	string message = currentFile->Save();
	return message;
}

string Controller::SaveAs(string path)
{
	string message = currentFile->SaveAs(path);
	return message;
}

string Controller::Help()
{
	std::string output = "";
	output += "The following commands are supported :\n";
	output += "close........................................................closes currently opened file\n";
	output += "save.........................................................saves the currently opened files\n";
	output += "saveas <file>................................................saves the first open file in <file>\n";
	output += "help.........................................................prints this information\n";
	output += "exit.........................................................exists the program\n";
	output += "print........................................................print all the figures\n";
	output += "create.......................................................creates a figure. For example: create rectangle 1 1 2 3 green\n";
	output += "erase <n>....................................................erases the n-th figure\n";
	output += "translate vertical:<value> horizontal:<value> [n]...........translates the n-th figure or all if n is not spesified\n";
	output += "within <option> .............................................print all the figure who are within the <option=(rectangle,circle)>\n";
	output += "clear........................................................clears the screen";
	return output;
}

void Controller::Exit()
{
	throw std::string("Exiting the program...");
}

string Controller::Print()
{
	string output = "";
	std::vector<block<Shape*>> shapes;
	int counter = 1;
	for (size_t i = 0; i < files.size(); i++)
	{
		shapes = files[i].GetShapes();

		for (size_t j = 0; j < shapes.size(); j++)
		{
			for (size_t k = 0; k < shapes[j].data.size(); k++)
			{
				output +=std::to_string(counter) + ". " + shapes[j].data[k]->ToStringPrint();
				output += "\n";
				counter++;
			}
		}
	}
	return output;
}

string Controller::Create(std::vector<std::string> tokens)
{
	return "";
}

string Controller::Erase(int)
{
	return string();
}

string Controller::Translate(int vertical, int horizontal,int possition)
{
	string message = "";
	if (possition == -1)
	{
		std::vector<block<Shape*>> shapes;
		int counter = 1;
		for (size_t i = 0; i < files.size(); i++)
		{
			shapes = files[i].GetShapes();

			for (size_t j = 0; j < shapes.size(); j++)
			{
				for (size_t k = 0; k < shapes[j].data.size(); k++)
				{
					shapes[j].data[k]->Translate(vertical, horizontal);
				}
			}
		}

		message += "Translated all figures.";

	}
	else if(possition >= 1)
	{
		int counter = 0;
		std::vector<block<Shape*>> shapes;
		for (size_t i = 0; i < files.size(); i++)
		{
			shapes = files[i].GetShapes();

			for (size_t j = 0; j < shapes.size(); j++)
			{
				for (size_t k = 0; k < shapes[j].data.size(); k++)
				{
					counter++;
					if (counter == possition)
					{
						shapes[j].data[k]->Translate(vertical, horizontal);
						return "Translated figure: " + std::to_string(counter);
					}
				}
			}
		}
	}
	return message;
}

string Controller::Within(std::vector<string>&)
{
	return string();
}
