#pragma once
#include<vector>
#include"Shape.h"

template <class T>
class Repository
{
public:
	Repository()
	{

	}
	void Create(T* item)
	{
		items.push_back(item);

	}
	T* Read(int pos)
	{
		if (IsValid(pos))
		{
			return items[pos - 1];
		}
		else
		{
			return NULL;
		}
	}
	bool Delete(int pos)
	{
		if (IsValid(pos))
		{
			for (size_t i = pos-1; i < items.size()-1; i++)
			{
				items[i] = items[i + 1];
			}
			items.pop_back();
			return true;
		}
		else
		{
			return false;
		}
	}

	size_t Size() const
	{
		return items.size();
	}

private:
	std::vector<T*> items;
	bool IsValid(int pos)
	{
		bool condition = (!items.empty()) && 1 <= pos && pos <= (int)items.size();
		return condition;
	}
};

