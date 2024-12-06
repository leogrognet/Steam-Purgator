#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"
#include "Weapons.h"


using namespace std;
using namespace sf;

#ifndef PLAYER_H
#define	PLAYER_H



class Player {
public:
	Player(int hp, int maxHp, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);
	~Player();


	void movement();
	void attack();
	void destroyPlayer();
	void initBullets();



private:
	enum Direction{Up,Down,Left,Right};
	enum Attacks{LeftAttack,RightAttack,ChangeAttack};
	float pos_x, pos_y;
	float size_x, size_y;
	float speed;
	bool alive;
	int health;
	int maxHealth;
	RectangleShape playerSprite;
	map<Direction, Keyboard::Key> DirectionBind;
	map<Attacks, Keyboard::Key> AttackBind;
};


#endif