#include <string>
#include <iostream>

using namespace System;
using std::string;

#pragma once
class Vessel
{
public:
	Vessel();//default constructor
	Vessel(string name, int hp, int speed, int atkDistance, int atdCD,
		int defDistance, int defCD, int damage, int shellSpeed, int x, int y);

	void tag(string newName);
private:
	string name;
	int hp;
	int speed;
	int atkDistance;
	int atdCD;
	int defDistance;
	int defCD;
	int damage;
	int shellSpeed;
	int x;
	int y;
};

class DD : public Vessel {
public:
	DD();
	DD(string name, int x, int y);
private:
};

class CV : public Vessel {
public:
	CV();
	CV(string name, int x, int y);
private:
};

class CG : public Vessel {
public:
	CG();
	CG(string name, int x, int y);
private:
};

class BB : public Vessel {
public:
	BB();
	BB(string name, int x, int y);
private:
};