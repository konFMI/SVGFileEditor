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
    std::string output = "";
    output += "<rect x=\"" + std::to_string(x) + "\" y=\"" + std::to_string(y) + "\" width=\"" + std::to_string(width) + "\" height=\"" + std::to_string(height) + "\" fill=\"" + fill + "\" />";
    return output;
}

void Rectangle::Translate(int vertical, int horizontal)
{
    if ((x + horizontal) >= 0 && (y+vertical) >= 0)
    {
        x += horizontal;
        y += vertical;
    }
}

bool Rectangle::WithinCircle(int cx, int cy, int r)
{
    bool condition = (x <= (cx - r) && (cx + r) <= (x + width)) && (y <= (cy - r) && (cy + r) <= (y + height));
    return condition;
}

bool Rectangle::WithinRectangle(int xR, int yR, int widthR, int heightR)
{
    bool condition = 
        (xR <= x && (x + width) < (xR + widthR)) &&
        (yR < y && (y + height) < (yR + heightR));
    return condition;
}
