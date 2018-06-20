#include "Vessel.h"

Vessel::Vessel()
{
}

Vessel::Vessel(string name, string type, int hp, int speed, int atkDistance, int atkCD, int defDistance, int defCD, int damage, int shellSpeed, float x, float y)
{
	this->type = type;
	this->hp = hp;
	this->speed = speed;
	this->atkDistance = atkDistance;
	this->atkCD = atkCD;
	this->defDistance = defDistance;
	this->defCD = defCD;
	this->damage = damage;
	this->shellSpeed = shellSpeed;
	this->atkCurrent = 0;
	this->defCurrent = 0;
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

DD::DD(string name, string type, float x, float y) : Vessel(name, type, 2, 3, 10, 15, 20, 60, 1, 3, x, y)
{
}

CV::CV()
{
}

GG::GG(string name, string type, float x, float y) : Vessel(name, type, 10, 8, 29, 1, 20, 1000,1000, 100, x, y)
{
}

GG::GG()
{
}

CV::CV(string name, string type, float x, float y) : Vessel(name, type, 5, 1, 25, 60, 5, 15, 3, 4, x, y)
{
}

CG::CG()
{
}

CG::CG(string name, string type, float x, float y) : Vessel(name, type, 3, 2, 15, 30, 15, 30, 2, 3, x, y)
{
}

BB::BB()
{
}

BB::BB(string name, string type, float x, float y) : Vessel(name, type, 4, 1, 20, 30, 10, 30, 3, 2, x, y)
{
}