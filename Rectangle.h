#pragma once
#include "Shape.h"
class Rectangle :
    public Shape
{
    Rectangle();

    // Inherited via Shape
    virtual std::string ToStringPrint() override;
    virtual std::string ToStringFile() override;
};

