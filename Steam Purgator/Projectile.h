#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;


#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile {
public:
	Projectile();
	
	Projectile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);
	virtual ~Projectile();
	

	const Vector2f& getPos() const;
	const FloatRect getBounds() const;
	
	Sprite getSprite();

	virtual void updateSelf();
	void renderProjectile(RenderWindow* target);

	

protected:
	Sprite sprite;
	float speed;


};

//-------------------------------------------------------------------------------------
//Class Missile------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

class Missile : public Projectile {
public:
	Missile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, vector<Sprite*>& enemiesSprites);
	void updateSelf() override;

private:
	vector<Sprite*>& enemiesSprites;  // Liste des sprites ennemis
	Sprite* targetSprite = nullptr;  // Pointeur vers le sprite ciblé
	Vector2f direction;
};


//-------------------------------------------------------------------------------------
//Class Laser------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
class Laser : public Projectile {
public:
	Laser(Texture* texture, float size_x, float size_y, float pos_x, float pos_y);
	void updateSelf() override;
	bool active;
};


//-------------------------------------------------------------------------------------
//Class Shield------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
class Shield : public Projectile {
public:
	Shield(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);
	void updateSelf() override;
};


//-------------------------------------------------------------------------------------
//Class Bomb------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
class Bomb : public Projectile {
public:
	Bomb(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed);
	void updateSelf() override;
};



#endif // !WEAPONS_HPP
