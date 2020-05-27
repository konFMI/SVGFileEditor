#include "Controller.h"


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
	string message = "";
	if (files.size() > 1)
	{
		files.pop_back();
		currentFile = &files[files.size() - 1];
		message = "Closed \"" + currentFile->FileName() + "\"";
	}
	else if(files.size() == 1)
	{
		message = "Closed \"" + currentFile->FileName() + "\"";
		currentFile = NULL;
		files.pop_back();
	}
	return message;
}

string Controller::Save()
{
	if (currentFile->FileName().length() == 0)
	{
		throw std::string("The file doesn't have default path. Please use \"saveas\" to provide a path.");
	}
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
	if (!currentFile)
	{
		currentFile = new WorkingFile();
	}
	std::string output = currentFile->CreateShape(tokens);
	if (files.size() > 0)
	{
		files.pop_back();
	}

	files.push_back(*currentFile);
	return output;
}

string Controller::Erase(int position)
{
	std::string message = "There is no figure with number " + std::to_string(position);
	int counter = 1;
	for (int i = files.size() - 1; i >= 0; i--)
	{
		for (int j = 0; j < files[i].GetShapes().size(); j++)
		{
			for (int k = 0; k < files[i].GetShapes()[j].data.size(); k++)
			{
				if (counter == position)
				{
					for (int p = counter - 1; p < files[i].GetShapes()[j].data.size() - 1; p++)
					{
						files[i].GetShapes()[j].data[p] = files[i].GetShapes()[j].data[p + 1];
					}
					files[i].GetShapes()[j].data.pop_back();
					message = "Figure with number " + std::to_string(position) + " has been deleted.";
					return message;
				}
				else
				{
					counter++;
				}

			}
		}
	}
	return message;
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

string Controller::Within(std::vector<string>& params)
{
	std::vector<Shape*> shapesWithin;
	if (params.size() == 4 && params[0] == "circle")
	{
		int x = 0, y = 0, r = 0;
		if (StringToInt(params[1],x) && StringToInt(params[2], y)&& StringToInt(params[3], r))
		{
			for (size_t i = 0; i < files.size(); i++)
			{
				

				for (size_t j = 0; j < files[i].GetShapes().size(); j++)
				{
					for (size_t k = 0; k < files[i].GetShapes()[j].data.size(); k++)
					{
						if (files[i].GetShapes()[j].data[k]->WithinCircle(x,y,r))
						{
							shapesWithin.push_back(files[i].GetShapes()[j].data[k]);
						}
					}
				}
			}
		}
	}
	else if (params.size() == 5 && params[0] == "rectangle")
	{
		int x = 0, y = 0,width = 0,height = 0;
		if (StringToInt(params[1], x) && StringToInt(params[2], y) && StringToInt(params[3],width) && StringToInt(params[4],height))
		{
			for (size_t i = 0; i < files.size(); i++)
			{
				for (size_t j = 0; j < files[i].GetShapes().size(); j++)
				{
					for (size_t k = 0; k < files[i].GetShapes()[j].data.size(); k++)
					{
						if (files[i].GetShapes()[j].data[k]->WithinRectangle(x, y,width,height))
						{
							shapesWithin.push_back(files[i].GetShapes()[j].data[k]);
						}
					}
				}
			}
		}
	}
	std::string output = "";
	for (size_t i = 0; i < shapesWithin.size(); i++)
	{
		output += std::to_string(i) + ". " + shapesWithin[i]->ToStringPrint() + "\n";
	}

	return output;
}

string Controller::Translate(std::vector<std::string> tokens)
{
	std::string message = "";
	size_t size = tokens.size();
	std::vector<string> firstParameter, secondParameter;
	int vertical = 0, horizontal = 0, shapeIndex = -1;

	switch (size)
	{
	case 2:
		SplitInput(tokens[1], firstParameter, std::vector<char>{'='});
		if (firstParameter.size() == 2)
		{
			if (firstParameter[0] == "vertical" && StringToInt(firstParameter[1],vertical))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else if (firstParameter[0] == "horizontal" && StringToInt(firstParameter[1], horizontal))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else
			{
				message = "Invalid input.";
			}


		}
		else
		{
			message = "Invalid input.";

		}
		break;
	case 3:
		SplitInput(tokens[1], firstParameter, std::vector<char>{'='});
		SplitInput(tokens[2], secondParameter, std::vector<char>{'='});

		if (firstParameter.size() == 2)
		{
			if (firstParameter[0] == "vertical" && secondParameter.size() == 2 && secondParameter[0] == "horizontal" && StringToInt(firstParameter[1], vertical) && StringToInt(secondParameter[1], horizontal))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else if (firstParameter[0] == "horizontal" && secondParameter.size() == 2 && secondParameter[0] == "vertical" && StringToInt(firstParameter[1], horizontal) && StringToInt(secondParameter[1], vertical))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else if (firstParameter[0] == "vertical" && secondParameter.size() == 1 && StringToInt(firstParameter[1], vertical) && StringToInt(secondParameter[0], shapeIndex))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else if (firstParameter[0] == "horizontal" && secondParameter.size() == 1 && StringToInt(firstParameter[1], horizontal) && StringToInt(secondParameter[0], shapeIndex))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else
			{
				message = "Invalid input.";
			}
		}
		else
		{
			message = "Invalid input.";
		}
		break;
	case 4:
		SplitInput(tokens[1], firstParameter, std::vector<char>{'='});
		SplitInput(tokens[2], secondParameter, std::vector<char>{'='});
		if (firstParameter.size() == 2 && secondParameter.size() == 2 && StringToInt(tokens[3], shapeIndex))
		{
			if (firstParameter[0] == "vertical" && secondParameter[0] == "horizontal"  && StringToInt(firstParameter[1], vertical) && StringToInt(secondParameter[1], horizontal))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else if (firstParameter[0] == "horizontal" && secondParameter[0] == "vertical" && StringToInt(firstParameter[1], horizontal) && StringToInt(secondParameter[1], vertical))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else
			{
				message = "Invalid input.";
			}
		}
		else
		{
			message = "Invalid input.";
		}
		break;
	default:
		message = "Invalid input.";
		break;
	}

	return message;
}

void Controller::SplitInput(std::string& input, std::vector<std::string>& tokens, std::vector<char> delimiters)
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





