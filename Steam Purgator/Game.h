#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"
#include "Projectile.h"
#include "Player.h"
#include "LoadTexture.cpp"



using namespace std;
using namespace sf;

#ifndef GAME_H
#define	GAME_H

class Game {
private :
public:
	vector<Projectile> allProjectiles;
	Game();
	~Game();
	void updatePlayer(Player& player, RenderWindow& window);
	void updateEnemy();
	void updateProjectile(RenderWindow& window);
	void updateConfig();
	Player player;
	int count=0;

};


#endif