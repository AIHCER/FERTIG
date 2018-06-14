#include <iostream>
#include <string>

#include "Base.h"

using std::string;

#pragma once
class Shell : public Base
{
public:
	Shell(string, float originX, float originY, float disX, float disY, float xSpeed, float ySpeed, float r, int damage);
	float originX;
	float originY;
	float disX;
	float disY;
	float xSpeed;
	float ySpeed;
	float r;
	int damage;
	string teamName;
private:
};