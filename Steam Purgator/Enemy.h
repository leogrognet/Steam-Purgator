#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;


#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:

	Enemy();

	Enemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);
	virtual ~Enemy();


	const Vector2f& getPos() const;
	const FloatRect getBounds() const;

	virtual const bool canAttack();

	virtual void updateSelf();
	void renderEnemy(RenderWindow* target);
	Sprite getSprite();
	float getSpeed();

	

	void setSpeed(float speed);


protected:
	Sprite sprite;
	float speed;
	Clock shootClock;
	Time shootTime;
	float attackCooldownMax;

};


class RangedEnemy : public Enemy {
public:

	RangedEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);


	void updateSelf() override;


	const bool canAttack() override;

private:

};

class CloseRangeEnemy : public Enemy {
public:

	CloseRangeEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);


	void updateSelf() override;


	const bool canAttack() override;

private:

};


#endif // !WEAPONS_HPP
