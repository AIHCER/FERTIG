#include "Shell.h"



Shell::Shell()
{
}

Shell::Shell(float originX, float originY, float disX, float disY, float xSpeed, float ySpeed, float r, int damage)
{
	this->originX = originX;
	this->originY = originY;
	this->disX = disX;
	this->disY = disY;
	this->xSpeed = xSpeed;
	this->ySpeed = ySpeed;
	this->r = r;
	this->damage = damage;
}
