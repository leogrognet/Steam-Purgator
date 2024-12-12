#define _USE_MATH_DEFINES
#include "SFML/Graphics.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;



#ifndef ENEMY_H
#define ENEMY_H

class BigEnemy {
public:

	BigEnemy();

	BigEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, float mult);
	virtual ~BigEnemy();


	const Vector2f& getPos() const;
	const FloatRect getBounds() const;

	int getHealth();

	virtual const bool canAttack();

	virtual void updateSelf(RenderWindow* window);
	void renderEnemy(RenderWindow* target);
	Sprite getSprite();
	float getSpeed();
	int getDamage();
	
	virtual void setHealth(int hp);
	virtual void setSpeed(float speed);
	virtual void setDamage(int dmg);

protected:
	bool move_count;
	int startX;
	int startY;
	float amplitudeX;
	float amplitudeY;
	float frequencyX;
	float frequencyY;
	Sprite sprite;
	float speed;
	int health;
	int damage;
	Clock shootClock;
	Time shootTime;
	Clock moveClock;
	Time moveTime;
	float attackCooldownMax;
	bool isMovingLeft = true;
	float totalTime;
};

class RangedEnemy : public BigEnemy {
public:
	RangedEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);

	void updateSelf(RenderWindow* window) override;
	void setSpeed(float speed) override;

private:
	float amplitudeY;  // Amplitude de mouvement vertical
	float frequencyY;  // Fréquence de l'oscillation verticale
	float startY;      // Position de départ verticale
	float startX;      // Position de départ horizontale (garde la position initiale en X)
	float horizontalSpeed; // Vitesse du déplacement horizontal
};




class CloseRangeEnemy : public BigEnemy {
public:

	CloseRangeEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, Vector2f playerPos);


	void updateSelf(RenderWindow *window) override ;

	void setSpeed(float speed) override;

private:
	enum class Direction
	{
		DiagonalLeftUp,
		SinusoidalDown,
		DiagonalRightUp
	};
	Vector2f direction;
	float diagonalSpeedX;
	float diagonalSpeedY;
	float amplitudeSpeedFactor = 0.002f;


};


#endif // !WEAPONS_HPP
