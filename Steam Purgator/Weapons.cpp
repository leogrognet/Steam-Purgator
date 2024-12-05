#include "Weapons.h"

AllWeapons::AllWeapons(Texture texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed) : size_x(size_x), size_y(size_y), pos_x(pos_x), pos_y(pos_y), alive(alive)
{
}

AllWeapons::~AllWeapons()
{
}

void AllWeapons::setCollision(bool collision)
{
	this->collision = collision;
}

void AllWeapons::setDamage(int damage)
{
	this->damage = damage;
}

