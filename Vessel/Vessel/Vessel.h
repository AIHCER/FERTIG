#pragma once
#include <iostream>
#include <string>
using namespace std;

class Vessel {
public:
	Vessel();//default constructor
	Vessel(string name, int hp, int speed, int atkDistance, int atdCD, 
		   int defDistance, int defCD, int damage, int shellSpeed, int x, int y);

	void tag(string newName);//重新命名船隻
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