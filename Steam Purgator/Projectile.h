#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;


#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile {
public:
	Projectile();
	
	Projectile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, float speed, int damage);
	virtual ~Projectile();
	
	bool active;

	Texture* texture;

	const Vector2f& getPos() const;
	const FloatRect getBounds() const;
	
	Sprite getSprite();


	virtual void updateSelf(Sprite enemySprite = Sprite(), Sprite playerSprite = Sprite());
	virtual void renderProjectile(RenderWindow* target);
	void markForRemoval();
	bool isMarkedForRemoval() const;
	void updateAnim();
	int getDamage();
	bool isClosest = false;
protected:	
	bool markedForRemoval;
	Sprite sprite;
	float speed;

	Clock AnimClock;
	Time AnimTime;
	int damage;
	int ammo;
	int max_ammo;
	int top;
	int left;
	int width;
	int height;
	
	
	Vector2f deltaTexture;

};

//-------------------------------------------------------------------------------------
//Class Missile------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

class Missile : public Projectile {
public:
	Missile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, float speed, int left, int top, int width, int height, int damage);
	void updateSelf(Sprite enemySprite , Sprite playerSprite = Sprite()) override ;
	//Sprite* findClosestEnemy(const sf::Sprite& referenceSprite, const std::vector<sf::Sprite>& allEnemies);
	Vector2f direction;
private:
	//vector<Sprite*>& enemiesSprites;  // Liste des sprites ennemis
	//Sprite* targetSprite = nullptr;  // Pointeur vers le sprite ciblé
	
};


//-------------------------------------------------------------------------------------
//Class Laser------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
class Laser : public Projectile {
public:
	Laser(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, Sprite player,int damage);
	void updateSelf(Sprite sprite, Sprite player ) override;
	void renderProjectile(RenderWindow* target) override;
	void setActive(bool setter);
	void followPlayer(Sprite player);
	Sprite tempSprite;
private:
	
	bool checkLaserCollisionWithEnemy(const Vector2f& laserStart, const Vector2f& laserDirection, float laserLength, const Sprite& enemySprite);
	float calculateCollisionDistance(const Vector2f& laserStart, const Vector2f& laserDirection, const Sprite& enemySprite);
	
};


//-------------------------------------------------------------------------------------
//Class Shield------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
class Shield : public Projectile {
public:
	Shield(Texture* texture, float size_x, float size_y, float pos_x, float pos_y);
	void setActive(bool setter);
	void followPlayer(Sprite player);
	void renderProjectile(RenderWindow* target);
};


//-------------------------------------------------------------------------------------
//Class Bomb------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
class Bomb : public Projectile {
public:
	Bomb(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, float speed, int left, int top, int width, int height);

};


class FlameBall : public Projectile {
public:
	FlameBall(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, float speed, float angle, int damage);
	void updateSelf();
	Vector2f calculateDirection(float angleInDegrees);
private:
	float angle;
};


#endif // !WEAPONS_HPP
