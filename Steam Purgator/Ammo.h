#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

#pragma once

class Ammunition {
public:

	Ammunition(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, float speed, int AmmoType);
	~Ammunition();

	Sprite sprite;
	Texture* texture;
	
	void updateSelf();
	void markForRemoval();
	bool isMarkedForRemoval() const;
	void Ammochoice();

	int getAmmo();
	void setAmmoMax(int AmmoMax);

	int getAmmoMax();


	void renderAmmo(RenderWindow* target);


protected:
	bool markedForRemoval;
	float speed;
	int AmmoMax;
	int Ammo;
	
};