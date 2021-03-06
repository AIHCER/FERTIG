#include <string>
#include <iostream>

#include "Base.h"

using namespace System;
using std::string;

#pragma once
class Vessel : public Base
{
public:
	Vessel();//default constructor
	Vessel(string name, string type, int hp, int speed, int atkDistance, int atdCD,
		int defDistance, int defCD, int damage, int shellSpeed, float x, float y);
	void tag(string newName);
	string getType() { return type; };

	int hp;
	int speed;
	int atkDistance;
	int atkCurrent;
	int atkCD;
	int defDistance;
	int defCurrent;
	int defCD;
	int damage;
	int shellSpeed;
	float xSpeed;
	float ySpeed;
	bool moveORnot;
	int minus = 0;
private:
	string type;

};

class DD : public Vessel {
public:
	DD();
	DD(string name, string type, float x, float y);
private:
};

class GG : public Vessel {
public:
	GG();
	GG(string name, string type, float x, float y);
private:
};

class CV : public Vessel {
public:
	CV();
	CV(string name, string type, float x, float y);
private:
};

class CG : public Vessel {
public:
	CG();
	CG(string name, string type, float x, float y);
private:
};

class BB : public Vessel {
public:
	BB();
	BB(string name, string type, float x, float y);
private:
};