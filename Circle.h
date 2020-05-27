#pragma once
#include "Shape.h"
class Circle :
    public Shape
{
public:
    Circle(std::string name, int cx, int cy, int r, std::string fill);

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
    virtual bool WithinCircle(int cx, int cy, int r) override;

    virtual bool WithinRectangle(int x, int y, int width, int height) override;

};

