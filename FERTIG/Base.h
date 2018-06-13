#pragma once
#include <string>

using namespace System;
using std::string;

class Base
{
public:
	Base();
	float getX() { return x; };
	float getY() { return y; };
	String ^ getName() { 
		return gcnew String (name.c_str()); };
	string getsName() { return name; };
	void setX(float X) { x = X; };
	void setY(float Y) { y = Y; };
	void setName(String ^ input) {
		const char* chars =
			(const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(input)).ToPointer();
		name = chars;
	};
	void setName(string input) { name = input; };
private:
	string name;
	float x;
	float y;
};

