#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;


#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile {
public:
	Projectile();
	
	Projectile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, float speed);
	virtual ~Projectile();
	
	Texture* texture;

	const Vector2f& getPos() const;
	const FloatRect getBounds() const;
	
	Sprite getSprite();

	virtual void updateSelf(Sprite sprite = Sprite());
	void renderProjectile(RenderWindow* target);
	void markForRemoval();
	bool isMarkedForRemoval() const;
	void updateAnim();

protected:	
	bool markedForRemoval;
	Sprite sprite;
	float speed;

	Clock AnimClock;
	Time AnimTime;

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
	Missile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, float speed, int left, int top, int width, int height);
	void updateSelf(Sprite sprite = Sprite()) override ;
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
	Laser(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, int left, int top, int width, int height);
	void updateSelf(Sprite sprite = Sprite()) override;
	bool active;
};


//-------------------------------------------------------------------------------------
//Class Shield------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
class Shield : public Projectile {
public:
	Shield(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, int left, int top, int width, int height);
	void updateSelf(Sprite sprite = Sprite()) override;
};


//-------------------------------------------------------------------------------------
//Class Bomb------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
class Bomb : public Projectile {
public:
	Bomb(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, float speed, int left, int top, int width, int height);
	void updateSelf(Sprite sprite = Sprite()) override;
};



#endif // !WEAPONS_HPP
