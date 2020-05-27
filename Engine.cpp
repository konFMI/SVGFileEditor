#include<iostream>
#include "Engine.h"

Engine::Engine()
{
}
void Engine::Run()
{
    std::string input;
    std::string command = "";
    std::string message = "";
    std::vector<std::string> tokens;

    while (true)
    {
        try {
            std::cout << "@>";
            std::getline(std::cin, input);
            tokens.clear();
            message = "";

            if (input.length() > 0)
            {
                SplitInput(input, tokens, std::vector<char > {' ', '\t', '\n'});
                if (!tokens.empty())
                {
                    command = tokens[0];
                    size_t size = tokens.size();

                    if (command == "open" && size == 2)
                    {
                        std::string path = tokens[1];
                        message = controller.Open(path);
                    }
                    else if (command == "close" && size == 1)
                    {
                        message = controller.Close();
                    }
                    else if (command == "save" && size == 1)
                    {
                        message = controller.Save();
                    }
                    else if (command == "saveas" && size == 2)
                    {
                        std::string path = tokens[1];
                        message = controller.SaveAs(path);
                    }
                    else if (command == "help" && size == 1)
                    {
                        message = controller.Help();
                    }
                    else if (command == "exit" && size == 1)
                    {
                        controller.Exit();
                    }
                    else if (command == "print" && size == 1)
                    {
                        message = controller.Print();
                    }
                    else if (command == "create" && size > 1)
                    {
                        // Removing the "create" from the collection.
                        for (size_t i = 0; i < tokens.size() - 1; i++)
                        {
                            tokens[i] = tokens[i + 1];
                        }
                        tokens.pop_back();

                        message = controller.Create(tokens);
                    }
                    else if (command == "erase" && size == 2)
                    {
                        int possition = StringToInt(tokens[1]);
                        message = controller.Erase(possition);
                    }
                    else if (command == "within")
                    {
                        //Removing the "withing" from the collection.
                        for (size_t i = 0; i < tokens.size() - 1; i++)
                        {
                            tokens[i] = tokens[i + 1];
                        }
                        tokens.pop_back();
                        if (!tokens.empty())
                        {
                            message = controller.Within(tokens);
                        }
                        else
                        {
                            message = "Invalid input.";
                        }
                    }
                    else if (command == "translate" && (size == 2 || size == 3 || size == 4))
                    {
                        message = controller.Translate(tokens);
                    }
                    else if (command == "clear" && size == 1)
                    {
                        system("CLS");
                    }
                    else
                    {
                        message = "Invalid command.";
                    }

                    if (message.length() > 0)
                    {
                        std::cout << message << std::endl;
                    }

                }
            }
        }
        catch (string ms)
        {
            std::cout << ms << std::endl;
            if (ms == "Exiting the program...")
            {
                break;
            }
        }
    }

}

void Engine::SplitInput(std::string& input, std::vector<std::string>& tokens,std::vector<char> delimiters)
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

int Engine::StringToInt(std::string& input)
{
    int num = 0;
    for (size_t i = 0; i < input.length(); i++)
    {
        if (isdigit(input[i]))
        {
            num *= 10;
            num += (input[i] - '0');
        }
        else if (i > 0)
        {
            throw std::string("Invalid input.");
        }
    }
    if (input.length() > 0 && input[0] == '-')
    {
        num *= (-1);
    }
    return num;
}
