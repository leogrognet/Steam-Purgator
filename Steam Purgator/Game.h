#include <memory>
#include <functional>
#include <cstdlib>
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"
#include "Ammo.h"
#include "setBackGround.h"
#include <thread>



using namespace std;
using namespace sf;

#ifndef GAME_H
#define	GAME_H

class Game {
private :
	RenderWindow* window;
	Vector2u screenSize;

	map<String, Texture*> playerProjectileTexture;
	map<String, Texture*> enemyProjectileTexture;
	map<String, Texture*> BackGroundTexture;
	map<String, Texture*> AmmoTexture;
	map<String, Texture*> enemyTextures;        
	map<String, Texture*> playerTextures;


	Sprite TourMap;
	Sprite Map;

	vector<Ammunition*> allAmmo;

	vector<Projectile*> allPlayerProjectiles;

	vector<Projectile*> allEnemyProjectiles;

	
	vector <BigEnemy*> allEnemies;
	unique_ptr<Player> player;
	unique_ptr<Laser> playerLaser;
	unique_ptr<Shield> playerShield;
	unique_ptr<setBG> levelBG;

	int currentWeapon;
	int currentLevel; 
	int levelDuration; 
	int enemySpawnInterval;

	bool Pause;

	bool enemy1, enemy2, enemy3;

	bool isBossKilled;
	Vector2f animP, animG, animB, animD;

	int score;

	bool game_on;
	Clock startClock;  
	Time startTimeElapsed;
	Clock deltaClock;
	Time deltaTimeElasped;

	void loadTexture(map<String, Texture*>& textureMap, const string& key, const string& path);
	void initPlayer();
	void initAmmo();
	void initProjectile();
	void initEnemy();
	void initBG();
	void initScoreText();
	int loadScoreFont();
	void allinit();

	Text ScoreText;
	Font font;
	Text lose;
	Text GameOverText;



	Clock animClock;          
	Vector2f animTourmap;    
	float animSpeed = 0.1f;

public:
	bool canSpawn;
	Game();
	virtual ~Game();

	bool run();
	
	void startLevel(int level);

	void deleteObjects();
	void spawnEnemy();
	void spawnBoss();
	int  GameOver();

	void updateInput();
	void updateBoss();
	void updateAmmo();
	void updateLevel();
	void updateEnemy();
	void updateProjectile();
	void updatePlayer();
	void updateBG();
	void update();

	int count=0;

	void render();

};



#endif