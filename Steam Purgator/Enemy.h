#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;


#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:

	Enemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);
	virtual ~Enemy();


	const Vector2f& getPos() const;
	const FloatRect getBounds() const;

	void updateSelf();
	void renderEnemy(RenderWindow* target);



private:
	Sprite sprite;
	float speed;


};

#endif // !WEAPONS_HPP
