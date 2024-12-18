#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"



using namespace std;
using namespace sf;

#ifndef PLAYER_H
#define	PLAYER_H



class Player {
public:
	Player(Texture* texture, Texture* healthTexture, Texture* textureMissile, Texture* textureLaser, Texture* textureBouclier , Texture* textureBombe, int maxHp, float size_x, float size_y, float pos_x, float pos_y, float speed, int left, int top, int width, int height);
	virtual ~Player();

	


	void movement(RenderWindow* window);
	int attack();


	const int& getHp() const;
	const int& getHpMax() const;
	const Vector2f& getPos() const;
	const FloatRect getBounds() const;
	const float getSpeed() const;
	const int getDamage() const;
	Sprite getSprite() ;
	const Texture getTexture() const;
	

	void loseHp(const int value);

	void setHp(const int hp);
	void setPosition(const Vector2f pos);
	void setPosition(const float x, const float y);
	

	const bool canAttack();


	void updateAnim();
	void update(RenderWindow* window);
	void render(RenderTarget& target);


	map<string, int> weaponCount = {
		{"missileUse",  15},
		{"laserUse", 50},
		{"shieldUse", 50},
		{"bombUse", 0}
	};

	
	enum Direction{Up,Down,Left,Right};
	enum Attacks{LeftAttack,RightAttack,ChangeAttack};
	map<Direction, Keyboard::Key> DirectionBind;
	map<Attacks, Keyboard::Key> AttackBind;

	

private:
	
	Texture* healthTexture;
	Sprite healthSprite;
	RectangleShape healthBar;


	Sprite NbMissile, NbLaser, NbBouclier, NbBombe;

	Texture *textureMissile, *textureLaser, *textureBouclier, *textureBombe;
	
	Texture* texture;
	Sprite playerSprite;
	

	Text IntMissile, IntLaser, IntBouclier, IntBombe;
	Font font;

	float speed;
	int MissileMax;
	int LaserMax;
	int BombMax;
	int ShieldMax;

	float size_x, size_y;

	Clock shootClock;
	Time shootTime;
	Clock AnimClock;
	Time AnimTime;


	int health;
	int maxHealth;
	int damage;
	
	float attackCooldownMax;

	int left, top, width, height;
	Vector2f deltaTexture;

	int loadAmmoFont();
	void initVariables();
	void initSprite();
	void initTextAmmo();


	

};
#endif
