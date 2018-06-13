#include "Vessel.h"

Vessel::Vessel()
{
}

Vessel::Vessel(string name, int hp, int speed, int atkDistance, int atdCD, int defDistance, int defCD, int damage, int shellSpeed, float x, float y)
{
	this->hp = hp;
	this->speed = speed;
	this->atkDistance = atkDistance;
	this->atdCD = atdCD;
	this->defDistance = defDistance;
	this->defCD = defCD;
	this->damage = damage;
	this->shellSpeed = shellSpeed;
	setX(x);
	setY(y);
	setName(name);
}

void Vessel::tag(string newName)
{
	setName(newName);
}

DD::DD()
{
}

DD::DD(string name, float x, float y) : Vessel(name, 2, 3, 10, 15, 20, 60, 1, 3, x, y)
{
}

CV::CV()
{
}

CV::CV(string name, float x, float y) : Vessel(name, 5, 1, 25, 60, 5, 15, 3, 4, x, y)
{
}

CG::CG()
{
}

CG::CG(string name, float x, float y) : Vessel(name, 3, 2, 15, 30, 15, 30, 2, 3, x, y)
{
}

BB::BB()
{
}

BB::BB(string name, float x, float y) : Vessel(name, 4, 1, 20, 30, 10, 30, 3, 2, x, y)
{
}