#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;


#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile {
public:
	
	Projectile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);
	virtual ~Projectile();
	

	const Vector2f& getPos() const;
	const FloatRect getBounds() const;
	
	void updateSelf();
	void renderProjectile(RenderWindow* target);

	

private:
	Sprite sprite;
	float speed;


};

#endif // !WEAPONS_HPP
