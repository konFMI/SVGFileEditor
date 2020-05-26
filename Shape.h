#pragma once
#include<string>
class Shape
{
	public:
		Shape()
		{

		}
		virtual void Translate(int, int) = 0;
		virtual std::string ToStringPrint() = 0;
		virtual std::string ToStringFile() = 0;
};

