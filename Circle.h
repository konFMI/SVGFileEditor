#pragma once
#include "Shape.h"
class Circle :
    public Shape
{
public:
    Circle(std::string,int, int, int, std::string);

    // Inherited via Shape
    virtual std::string ToStringPrint() override;
    virtual std::string ToStringFile() override;
private:
    std::string name;
    int cx;
    int cy;
    int r;
    std::string fill;
};

