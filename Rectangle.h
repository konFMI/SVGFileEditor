#pragma once
#include "Shape.h"
class Rectangle :
    public Shape
{
public:
    Rectangle(std::string,int,int,int,int,std::string);

    // Inherited via Shape
    virtual std::string ToStringPrint() override;
    virtual std::string ToStringFile() override;
    virtual void Translate(int, int) override;

private:
    std::string name;
    int x;
    int y;
    int width;
    int height;
    std::string fill;

};

