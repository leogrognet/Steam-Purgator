#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"



using namespace std;
using namespace sf;

#ifndef PLAYER_H
#define	PLAYER_H



class Player {
public:
	Player();
	~Player();


	void movement();
	void attack();
	void destroyPlayer();




	enum Direction{Up,Down,Left,Right};
	int pos_x, pos_y;
	float size_x, size_y;
	float speed;
	bool test;
	bool alive;
	int health;
	int maxHealth;
	RectangleShape playerSprite;
	map<Direction, Keyboard::Key> Keybind;
};


#endif