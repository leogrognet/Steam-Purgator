#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;


#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile {
public:
	Sprite sprite;
	Projectile(float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, Texture& texture);
	~Projectile();
	void updateSelf();
	void renderProjectile(RenderTarget* target);

private:
	float speed;
};

#endif // !WEAPONS_HPP
