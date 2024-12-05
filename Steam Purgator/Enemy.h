#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"



using namespace std;
using namespace sf;

#ifndef ENEMY_H
#define	ENEMY_H



class Enemy {
public:
	Enemy(Texture Texture,int hp, int maxHp, float size_x, float size_y, bool alive, float speed);
	~Enemy();


	void attack();
	void destroyEnemy(vector<Enemy&> listEnemy, int index);
	void setHealth(int health);
	int getHealth();
	vector<Sprite> enemyList;
	Sprite enemySprite;



private:
	int pos_x, pos_y;
	float size_x, size_y;
	float speed;
	bool test;
	bool alive;
	int health;
	int maxHealth;
	
};


#endif