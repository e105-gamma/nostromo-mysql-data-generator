#pragma once

#include "stdafx.h"
#include<string>
#include <boost\variant.hpp>

struct date {
	unsigned int day;
	unsigned int mounth;
	unsigned int year;
};


class SQLObject {

private:
	//int* intValue = nullptr; // can be replaced by std::variant
	//std::string* stringValue = nullptr;
	//date* dateValue = nullptr; 
	boost::variant<int,std::string> value;
public:

	
	template <typename  T>
	void setValue (T value) {

		if (std::is_same<T, int>::value) 
		{  
			this->value = value;
		}
		else if (std::is_same<T, std::string>::value) {
			this->value = value;
		}
		//else if (std::is_same<T, date>::value) {
		//	//*dataValue = value;
		//}
	}

	int getInt() {
		return  boost::get<int>(value);
	}

	std::string getString() {
		return  boost::get<std::string>(value);
	}
	
	//template <typename  T>
	//T getValue() {
	//	if (std::is_same<T, int>::value)
	//	{
	//		return value.
	//	}
	//	else if (std::is_same<T, std::string>::value) {
	//		return *stringValue;
	//	}
	//	//else if (std::is_same<T, date>::value) {
	//	//	return *dataValue;
	//	//}
	//	//else 
	//		//return NULL; 
	//}

};



