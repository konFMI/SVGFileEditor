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
    virtual void Translate(int, int) override;

private:
    std::string name;
    int cx;
    int cy;
    int r;
    std::string fill;


    // Inherited via Shape
    virtual bool WithinCircle(int,int,int) override;

    virtual bool WithinRectangle(int,int,int,int) override;

};

