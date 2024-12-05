#include "UpdateGame.h"

void Update::initPlayer(Texture Texture)
{
}

void Update::initEnemies(Texture Texture) {
	Enemy enemy(Texture);
	enemyList.push_back(enemy);
}