#pragma once
#include<string>
class Shape
{
	public:
		Shape();
		virtual std::string ToStringPrint() = 0;
		virtual std::string ToStringFile() = 0;
};

