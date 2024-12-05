#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Enemy.h"

using namespace sf;

#ifndef UPDATEGAME_H
#define UPDATEGAME_H


class Update {
public:
	void initTextures(Texture texture);
	void initPlayer(Texture Texture);
	void initEnemies(Texture Texture);


private:
	Player player;
	vector<Enemy> enemyList;

};


#endif // !UPDATEGAME_H



