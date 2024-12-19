#include"Game.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include "Enemy.h"
#include <vector>
#include <cstdlib>
#include "Projectile.h"
#include "Player.h"
#include "Ammo.h"
#include <memory>
#include <functional>
#include"setBackGround.h"
#include "Menu.h"


#ifndef EDITEUR_H
#define EDITEUR_H
class edit {
public:
	void loadTextureE(map<String, Texture*>& textureMap, const string& key, const string& path);
	RenderWindow* page;

	map<String, Texture*> enemyTexturesE;//
	map<String, Texture*> BGtxt;//
	map<String, Texture*> PlayerpE;//
	map<String, Texture*> EnemypE;//
	map<String, Texture*> Muntxt;//
	unique_ptr<Player> playerEd;
	unique_ptr<setBG> levelBGE;
	unique_ptr<Laser> playerLaser;
	unique_ptr<Shield> playerShield;
	bool E_BigEnemy = false;
	bool E_RangedEnemy = false;
	bool E_CloseRangeEnemy = false;
	bool E_Boss = false;
	bool Rt_menu = false;
	bool lancement = false;
	bool isBossKilledE = false;
	Clock spawnClick ;
	Time spawnClickTime;
	int clickCount[4] = { 0,0,0,0 };
	int Nbj;
	void edition();
	void spawnEnemyEditG();
	void spawnEnemyEditA();
	void spawnEnemyEditD();
	void spawnEnemyEditB();
	void inittxtE();
	void initMunE();
	void initP();
	void initPlayer();
	void initBG();
	void initallE();
	void ltdraw_ennemieE();
	void Memsuppr();

	void updateInputE();
	void updateAmmoE();
	void updateEnemyE();
	void updateProjectileE();
	void updatePlayerE();
	void updatebE();
	void updateBgE();
	void updateE();
	void render();
	Clock Eclock;
	Time startSpawn;
	vector <BigEnemy*> EnnemieG;
	vector<Ammunition*> allAmmoE;
	Text ScoreText;
	vector<Projectile*> allPlayerProjectilesE;

	vector<Projectile*> allEnemyProjectilesE;
	int score;
	int currentWeapon;
};
#endif