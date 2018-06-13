#include <iostream>
#include <string>

#include "Base.h"

using std::string;

#pragma once
class Shell : public Base
{
public:
	Shell();
	Shell(float originX, float originY, float disX, float disY, float xSpeed, float ySpeed, float r, int damage);
	float originX;
	float originY;
	float disX;
	float disY;
	float xSpeed;
	float ySpeed;
	float r;
	int damage;
private:
};