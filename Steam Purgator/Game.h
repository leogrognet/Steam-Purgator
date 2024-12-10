#include <memory>
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"




using namespace std;
using namespace sf;

#ifndef GAME_H
#define	GAME_H

class Game {
private :
	RenderWindow* window;

	Texture * playerProjectileTexture;
	Texture* enemyProjectileTexture;


	Texture* enemyTexture;

	vector<Projectile*> allPlayerProjectiles;

	vector<Projectile*> allEnemyProjectiles;

	vector <BigEnemy*> allEnemies;
	unique_ptr<Player> player;

	int score;

	bool game_on;
	Clock startClock;  
	Time startTimeElapsed;
	Clock deltaClock;
	Time deltaTimeElasped;
	void initPlayer();
	void initProjectile();
	void initEnemy();

public:
	
	Game();
	virtual ~Game();

	bool run();
	void updateInput();

	void spawnEnemy();
	void updateEnemy();
	void updateProjectile();
	void updatePlayer();
	void update();

	int count=0;

	void render();

};


#endif