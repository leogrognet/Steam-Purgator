#include <memory>
#include <functional>
#include <cstdlib>
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

	map<String, Texture*> playerProjectileTexture;
	map<String, Texture*> enemyProjectileTexture;
	map<String, Texture*> BackGroundTexture;
	map<String, Texture*> AmmoTexture;

	Sprite TourMap;

	vector<Projectile*> allPlayerProjectiles;

	vector<Projectile*> allEnemyProjectiles;

	map<String, Texture*> enemyTextures;

	vector <BigEnemy*> allEnemies;
	unique_ptr<Player> player;


	int currentWeapon;
	int currentLevel; 
	int levelDuration; 
	int enemySpawnInterval;
	Vector2f animP, animG, animB, animD;

	int score;

	bool game_on;
	Clock startClock;  
	Time startTimeElapsed;
	Clock deltaClock;
	Time deltaTimeElasped;
	void initPlayer();
	void initAmmo();
	void initProjectile();
	void initEnemy();
	void initBG();
	

	Clock animClock;            // Horloge pour contrôler l'animation
	Vector2f animTourmap;     // Frame actuelle de Tourmap (ou autre objet)
	float animSpeed = 0.1f;

public:
	
	Game();
	virtual ~Game();

	bool run();
	void updateInput();
	void startLevel(int level);

	void spawnEnemy();


	void updateLevel();
	void updateEnemy();
	void updateProjectile();
	void updatePlayer();
	void update();

	int count=0;

	void render();

};


#endif