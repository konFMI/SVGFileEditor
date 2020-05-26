#include "Circle.h"

Circle::Circle(std::string name,int cx, int cy, int r, std::string fill)
{
    if (cx < 0 || cy < 0 || r < 0)
    {
        throw std::string("Invalid argument.");
    }
    this->name = name;
    this->cx = cx;
    this->cy = cy;
    this->r = r;
    this->fill = fill;
}

std::string Circle::ToStringPrint()
{
    std::string output = "";
    output += name + " " + std::to_string(cx) + " " + std::to_string(cy) + " " + std::to_string(r) + " " + fill;
    return output;
}

std::string Circle::ToStringFile()
{
    return std::string();
}
