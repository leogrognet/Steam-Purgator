#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;


#ifndef ENEMY_H
#define ENEMY_H

class BigEnemy {
public:

	BigEnemy();

	BigEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);
	virtual ~BigEnemy();


	const Vector2f& getPos() const;
	const FloatRect getBounds() const;

	virtual const bool canAttack();

	virtual void updateSelf();
	void renderEnemy(RenderWindow* target);
	Sprite getSprite();
	float getSpeed();

	
	virtual void setHealth(int hp);
	virtual void setSpeed(float speed);
	virtual void setDamage(int dmg);

protected:
	Sprite sprite;
	float speed;
	int health;
	int damage;
	Clock shootClock;
	Time shootTime;
	float attackCooldownMax;

};


class RangedEnemy : public BigEnemy {
public:

	RangedEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);


	void updateSelf() override;

	void setSpeed(float speed) override;


private:

};

class CloseRangeEnemy : public BigEnemy {
public:

	CloseRangeEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);


	void updateSelf() override;

	void setSpeed(float speed) override;

private:

};


#endif // !WEAPONS_HPP
