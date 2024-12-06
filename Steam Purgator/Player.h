#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"



using namespace std;
using namespace sf;

#ifndef PLAYER_H
#define	PLAYER_H



class Player {
public:
	Player(int hp, int maxHp, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);
	~Player();


	void movement();
	int attack();


	const int& getHp() const;
	const int& getHpMax() const;

	void setPosition(const Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	const bool canAttack();

	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);





	
	enum Direction{Up,Down,Left,Right};
	enum Attacks{LeftAttack,RightAttack,ChangeAttack};
	map<Direction, Keyboard::Key> DirectionBind;
	map<Attacks, Keyboard::Key> AttackBind;


private:
	Texture texture;
	Sprite playerSprite;

	float speed;

	int health;
	int maxHealth;
	
	float attackCooldown;
	float attackCooldownMax;


	void initVariables();
	void initTexture();
	void initSprite();


	

};
#endif
