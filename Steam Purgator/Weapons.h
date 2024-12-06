#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;


#ifndef WEAPONS_H
#define WEAPONS_H

class AllWeapons {
public:
	AllWeapons(float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);
	~AllWeapons();
	void setCollision(bool collision);
	void setDamage(int damage);

private:
	float pos_x, pos_y;
	float size_x, size_y;
	float speed;
	bool alive;
	bool collision;
	int damage;
};

#endif // !WEAPONS_HPP
