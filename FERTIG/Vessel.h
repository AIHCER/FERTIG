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
	Vessel(string name, int hp, int speed, int atkDistance, int atdCD,
		int defDistance, int defCD, int damage, int shellSpeed, float x, float y);
	void tag(string newName);
private:
	int hp;
	int speed;
	int atkDistance;
	int atdCD;
	int defDistance;
	int defCD;
	int damage;
	int shellSpeed;
};

class DD : public Vessel {
public:
	DD();
	DD(string name, float x, float y);
private:
};

class CV : public Vessel {
public:
	CV();
	CV(string name, float x, float y);
private:
};

class CG : public Vessel {
public:
	CG();
	CG(string name, float x, float y);
private:
};

class BB : public Vessel {
public:
	BB();
	BB(string name, float x, float y);
private:
};