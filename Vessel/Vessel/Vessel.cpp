#include "Vessel.h"

Vessel::Vessel()
{
}

Vessel::Vessel(string name, int hp, int speed, int atkDistance, int atdCD, int defDistance, int defCD, int damage, int shellSpeed, int x, int y)
{
	this->name = name;
	this->hp = hp;
	this->speed = speed;
	this->atkDistance = atkDistance;
	this->atdCD = atdCD;
	this->defDistance = defDistance;
	this->defCD = defCD;
	this->damage = damage;
	this->shellSpeed = shellSpeed;
	this->x = x;
	this->y = y;
}

void Vessel::tag(string newName)
{
	name = newName;
}


