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
	Texture * playerProjectileTexture;
	Texture* enemyProjectileTexture;

	Texture* enemyTexture;

	vector<Projectile*> allPlayerProjectiles;

	vector<Projectile*> allEnemyProjectiles;

	vector <Enemy*> allEnemies;
	unique_ptr<Player> player;

	bool game_on;
	Clock startClock;  
	Time startTimeElapsed;
	Clock deltaClock;
	Time deltaTimeElasped;
	void initPlayer();
	void initProjectile();
	void initEnemy();

public:
	
	Game(RenderWindow* window);
	virtual ~Game();

	bool run(RenderWindow* window);
	void updateInput(RenderWindow* window);

	void spawnEnemy(RenderWindow* window);
	void updateEnemy();
	void updateProjectile(RenderWindow* window);
	void updatePlayer(RenderWindow* window);
	void update(RenderWindow* window);

	int count=0;

	void render(RenderWindow* window);

};


#endif