#include "Rectangle.h"

Rectangle::Rectangle(std::string name,int x,int y,int width,int height,std::string fill)
{
    if (x < 0 || y < 0 || width < 0 || height < 0)
    {
        throw std::string("Invalid argument.");
    }
    this->name = name;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->fill = fill;

}

std::string Rectangle::ToStringPrint()
{
    std::string output = "";
    output += name + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(width) + " " + std::to_string(height) + " " + fill;
    return output;
}

std::string Rectangle::ToStringFile()
{
    return std::string();
}
