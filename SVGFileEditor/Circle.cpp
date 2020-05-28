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
    std::string output = "";
    output += "<circle cx=\"" + std::to_string(cx) + "\" cy=\"" + std::to_string(cy) + " r=\"" + std::to_string(r) + "\" fill=\"" + fill + "\" />";
    return output;
}

void Circle::Translate(int vertical, int horizontal)
{
    if ((cx + horizontal) >= 0 && (cy + vertical) >= 0)
    {
        cx += horizontal;
        cy += vertical;
    }
}

bool Circle::WithinCircle(int cx, int cy, int r)
{
    double xd = cx - this->cx;
    double yd = cy - this->cy;
    double distance = sqrt(xd * xd + yd * yd);
    if (distance + this->r <= r)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Circle::WithinRectangle(int x,int y,int width ,int height)
{
    bool condition = (x <= (cx - r) && (cx + r) <= (x + width)) && (y <= (cy - r) && (cy + r) <= (y + height));
    return condition;
}

