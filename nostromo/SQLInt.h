#pragma once
#include "SQLObject.h"
class SQLInt :
	public SQLObject
{
public:
	SQLInt();
	~SQLInt();
	void setValue(int value);

private: 
	int value;
};

