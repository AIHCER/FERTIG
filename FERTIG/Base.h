#pragma once
#include <string>

using std::string;

class Base
{
public:
	Base();
	float getX() { return x; };
	float getY() { return y; };
	string getName() { return name; };
	void setX(float X) { x = X; };
	void setY(float Y) { y = Y; };
private:
	string name;
	float x;
	float y;
};

