#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"



using namespace std;
using namespace sf;

#ifndef ENEMY_H
#define	ENEMY_H



class Enemy {
public:
	Enemy();
	~Enemy();


	void attack();
	void destroyEnemy();




private:
	int pos_x, pos_y;
	float size_x, size_y;
	float speed;
	bool test;
	bool alive;
	int health;
	int maxHealth;
	RectangleShape enemySprite;
};


#endif