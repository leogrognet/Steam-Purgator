#include "Game.h"

void Game::updatePlayer()
{
}

Game::~Game()
{
	//Vidage de la memoire lors de la fermeture du jeu
	
	for (auto enemyProjectiles = this->allEnemyProjectiles.begin(); enemyProjectiles != this->allEnemyProjectiles.end();) {
		delete* enemyProjectiles;
		enemyProjectiles = this->allEnemyProjectiles.erase(enemyProjectiles);
	}
	for (auto playerProjectile = this->allPlayerProjectiles.begin(); playerProjectile != this->allPlayerProjectiles.end();) {
		delete* playerProjectile;
		playerProjectile = this->allPlayerProjectiles.erase(playerProjectile);
	}

	for (auto it = playerProjectileTexture.begin(); it != playerProjectileTexture.end(); ++it) {
		delete it->second;  
	}
	playerProjectileTexture.clear();

	for (auto it = enemyProjectileTexture.begin(); it != enemyProjectileTexture.end(); ++it) {
		delete it->second;  
	}
	enemyProjectileTexture.clear();

	for (auto it = BackGroundTexture.begin(); it != BackGroundTexture.end(); ++it) {
		delete it->second;  
	}
	BackGroundTexture.clear();

	delete this->window;
}



//-------------------------------------------------------------------------------------
//Fonction Init------------------------------------------------------------------------
//-------------------------------------------------------------------------------------


//fonction pour charger les textures
void Game::loadTexture(map<String, Texture*>& textureMap, const string& key, const string& path)
{
	textureMap[key] = new Texture;
	if (!textureMap[key]->loadFromFile(path)) {
		cout << "ERROR::Could not load texture: " << path << endl;
	}

}

//fonction pour initier les textures ou les objets du jeu

void Game::initPlayer()
{
	this->player = make_unique<Player>(100,100,2.0f,2.0f,500,500,false,10.f, "asset/SpriteAsset/Perso stu.png",54,30,54,30 );

}

void Game::initAmmo()
{

	this->loadTexture(this->AmmoTexture,"bombeMunition", "asset/SpriteAsset/mun Bombe.png");
	this->loadTexture(this->AmmoTexture, "laserMunition", "asset/SpriteAsset/mun laser.png");
	this->loadTexture(this->AmmoTexture, "missileMunition", "asset/SpriteAsset/mun missile.png");
	this->loadTexture(this->AmmoTexture, "bouclierMunition", "asset/SpriteAsset/mun bouclier.png");

}



void Game::initProjectile()
{
	this->loadTexture(this->playerProjectileTexture, "boulet", "asset/SpriteAsset/boulet de canon.png");
	this->loadTexture(this->playerProjectileTexture, "laser", "asset/SpriteAsset/laser.png");
	this->loadTexture(this->playerProjectileTexture, "missile", "asset/SpriteAsset/missile.png");
	this->loadTexture(this->playerProjectileTexture, "bouclier", "asset/SpriteAsset/bouclier.png");
	this->loadTexture(this->playerProjectileTexture, "bombe", "asset/SpriteAsset/Bombe.png");
	this->playerLaser = make_unique<Laser>(playerProjectileTexture["laser"], 1.0f, 1.0f, this->player->getPos().x + this->player->getBounds().width, this->player->getPos().y + this->player->getBounds().height / 2,this->player->getSprite());
	this->playerShield = make_unique<Shield>(playerProjectileTexture["bouclier"], 1.0f, 1.0f, this->player->getPos().x + this->player->getBounds().width, this->player->getPos().y + this->player->getBounds().height / 2);

	//Texture pour l'ennemi

	this->loadTexture(this->enemyProjectileTexture, "boulet", "asset/SpriteAsset/boulet de canon.png");
	this->loadTexture(this->enemyProjectileTexture, "bombe", "asset/SpriteAsset/Bombe.png");
}

void Game::initEnemy()
{
	this->loadTexture(this->enemyTextures, "Avion", "asset/SpriteAsset/Avion.png");
	this->loadTexture(this->enemyTextures, "Gargouille", "asset/SpriteAsset/gargouille.png");
	this->loadTexture(this->enemyTextures, "Dirigeable Ennemi", "asset/SpriteAsset/Dirigeable ennemie.png");
	this->loadTexture(this->enemyTextures, "Boss_1", "asset/SpriteAsset/Boss.png");
	
}

void Game::initBG()
{
	this->BackGroundTexture["Tour"] = new Texture;
	if (!this->BackGroundTexture["Tour"]->loadFromFile("asset/SpriteAsset/Tour.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}

	this->BackGroundTexture["1stMapVide"] = new Texture;
	if (!this->BackGroundTexture["1stMapVide"]->loadFromFile("asset/SpriteAsset/Map vide.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}
}



//fonction pour detruire un objet

void Game::deleteObjects() {
	// Nettoyer les ennemis
	this->allEnemies.erase(
		std::remove_if(
			this->allEnemies.begin(),
			this->allEnemies.end(),
			[](BigEnemy* enemy) {
				if (enemy->isMarkedForRemoval()) {
					delete enemy;
					return true;
				}
				return false;
			}),
		this->allEnemies.end()
	);

	// Nettoyer les projectiles du joueur
	this->allPlayerProjectiles.erase(
		std::remove_if(
			this->allPlayerProjectiles.begin(),
			this->allPlayerProjectiles.end(),
			[](Projectile* projectile) {
				if (projectile->isMarkedForRemoval()) {
					delete projectile;
					return true;
				}
				return false;
			}),
		this->allPlayerProjectiles.end()
	);

	// Nettoyer les projectiles ennemis
	this->allEnemyProjectiles.erase(
		std::remove_if(
			this->allEnemyProjectiles.begin(),
			this->allEnemyProjectiles.end(),
			[](Projectile* projectile) {
				if (projectile->isMarkedForRemoval()) {
					delete projectile;
					return true;
				}
				return false;
			}),
		this->allEnemyProjectiles.end()
	);

	// Nettoyer les Munitions
	this->allAmmo.erase(
		std::remove_if(
			this->allAmmo.begin(),
			this->allAmmo.end(),
			[](Ammunition* ammos) {
				if (ammos->isMarkedForRemoval()) {
					delete ammos;
					return true;
				}
				return false;
			}),
		this->allAmmo.end()
	);
}



//fonction de spawn des ennemies

void Game::spawnEnemy()
{
	deltaTimeElasped = deltaClock.getElapsedTime();
	this->startTimeElapsed = this->startClock.getElapsedTime();
	

		
		
		int min = 200;
		int max = window->getSize().y - min;

		int enemyX = window->getSize().x ;
		int enemyY = min + rand() % (max - min + 1);



		int enemyType = -1;
		int randomWeight = rand() % 100;

		if (startTimeElapsed.asSeconds() >= 30) {
			this->enemySpawnInterval = 2;
		}
		else if (startTimeElapsed.asSeconds() >= 120) {
			this->enemySpawnInterval = 1;
		}
		else if (startTimeElapsed.asSeconds() >= 180) {
			this->enemySpawnInterval = 0.5f;
		}

		if (randomWeight < 90) {
			if (this->startTimeElapsed.asSeconds() >= 3) {
				if (deltaTimeElasped.asSeconds() >= enemySpawnInterval) {
					enemyType = 0;
					deltaClock.restart();
				}
			}
		}

		if (randomWeight < 60) {
			if (this->startTimeElapsed.asSeconds() >= 15) {
				if (deltaTimeElasped.asSeconds() >= enemySpawnInterval) {
					enemyType = 1;
					deltaClock.restart();
				}
			}
		}
		

		if (randomWeight < 10) {
			if (this->startTimeElapsed.asSeconds() >= 20) {
				if (deltaTimeElasped.asSeconds() >= enemySpawnInterval) {
					enemyType = 2;
					deltaClock.restart();
				}
			}
		}
		

		Texture* selectedTexture = nullptr;
		switch (enemyType) {
		case 0:
			selectedTexture = enemyTextures["Gargouille"];
			break;
		case 1:
			selectedTexture = enemyTextures["Avion"];
			break;
		case 2:
			selectedTexture = enemyTextures["Dirigeable Ennemi"];
			break;
		}

		if (selectedTexture) {
			switch (enemyType) {
			case 0:
				this->allEnemies.push_back(new CloseRangeEnemy(

					selectedTexture, 2.0f, 2.0f, enemyX, enemyY, false, 10.f, this->player->getPos(), 
				100, 100, 100, 100
				));
				break;
			case 1:
				this->allEnemies.push_back(new RangedEnemy(
					selectedTexture, 1.5f, 1.5f, enemyX, enemyY, false, 10.f
				));
				break;
			
			case 2:
				this->allEnemies.push_back(new BigEnemy(
					selectedTexture, 3.0f, 3.0f, enemyX, enemyY, false, 10.f, 1.5f, 
					47, 31,47,31
				));
				break;
			}
		}
	}



//fonction de spawn du boss

void Game::spawnBoss()
{
	this->allEnemies.push_back(new Boss_1(enemyTextures["Boss_1"], 1.0f, 1.0f, 400.f, 400.f, true, 1.0f, 274, 273, 274, 273));
}




//fonction qui start le un niveau

void Game::startLevel(int level) {
	this->currentLevel = level;
	this->allEnemies.clear();  // Nettoyer les ennemis existants
	this->allPlayerProjectiles.clear();
	this->allEnemyProjectiles.clear();

	// Configurer des paramètres spécifiques au niveau
	switch (level) {
	case 1:
		this->levelDuration = 5; // Durée du niveau 1 (en secondes)
		this->enemySpawnInterval = 3; // Temps entre les spawns d'ennemis
		break;
	case 2:
		this->levelDuration = 90; // Durée du niveau 2 (en secondes)
		this->enemySpawnInterval = 2; // Temps entre les spawns d'ennemis
		break;
	default:
		cerr << "Level not implemented!" << endl;
		break;
	}
}




//-------------------------------------------------------------------------------------
//Fonction Run-------------------------------------------------------------------------
//-------------------------------------------------------------------------------------


//fonction pour lancer le jeu
bool Game::run() {
	startClock.restart();
	startTimeElapsed = startClock.getElapsedTime();
	this->game_on = true;
	

	while (game_on) {
		Event gameEvent;
		while (this->window->pollEvent(gameEvent)) {
			if (gameEvent.type == Event::Closed) {
				this->window->close();
			}
			if (gameEvent.type == Event::KeyPressed && gameEvent.key.code == Keyboard::Escape) {
				this->game_on = false;
			}
		}
		

		
		// Mise à jour du jeu
		this->update();
		

		// Rendu des objets à l'écran
		this->render();
	}

	return this->game_on;
}






//-------------------------------------------------------------------------------------
//Fonction Update----------------------------------------------------------------------
//-------------------------------------------------------------------------------------


//input du joueur et les interactions avec lui
void Game::updateInput()
{
	this->player->movement(window);

	if (this->player->attack() == 1 && this->player->canAttack())
	{
			this->allPlayerProjectiles.push_back(new Projectile(playerProjectileTexture["boulet"],
				5.0f,
				5.0f,
				this->player->getBounds().left + this->player->getBounds().width,
				this->player->getBounds().top + (this->player->getBounds().height / 2),
				1.f + this->player->getSpeed()
			)
			);
	}
	if (this->player->attack() == 2) { 
		switch (currentWeapon) {
		case 1:
		case 2:
			if (this->player->canAttack() && this->player->weaponCount["missileUse"] > 0) {
				this->allPlayerProjectiles.push_back(new Missile(playerProjectileTexture["missile"], 1.0f, 1.0f, this->player->getSprite().getPosition().x, this->player->getSprite().getPosition().y, 1.f + this->player->getSpeed(), 63, 21, 63, 21));
			}
			break;
		case 3:
			if (this->player->weaponCount["laserUse"] > 0){
				this->playerLaser->setActive(true);
			}
			break;

		case 4:
			if (this->player->weaponCount["shieldUse"] > 0) {
				this->playerShield->setActive(true);
			}
			break;
		}
	}
	else {
		this->playerLaser->setActive(false); 
		this->playerShield->setActive(false);
	}


	if (this->player->attack() == 3) {
		if (this->player->attack() == 3 && player->canAttack()) {
			currentWeapon++;
			if (currentWeapon > 4) {
				currentWeapon = 1;
			}
			
		}

	}
}







//fonction pour mettre a jour le boss

void Game::updateBoss()
{
	for (auto boss : allEnemies) {

		if (typeid (boss) == typeid (Boss_1)) {
			boss->updateSelf(window);
		}
	}
}



//fonction pour mettre a jour les munitons

void Game::updateAmmo()
{
	for (auto Ammo : allAmmo) {
		Ammo->updateSelf();
		if (Ammo->sprite.getGlobalBounds().height + Ammo->sprite.getPosition().y > window->getSize().y) {
			Ammo->markForRemoval();
		}
		if (Ammo->sprite.getGlobalBounds().intersects(this->player->getSprite().getGlobalBounds())) {
			switch (Ammo->getAmmo())
			{
			case 1:
				this->player->weaponCount["missileUse"] += Ammo->getAmmoMax();
				Ammo->markForRemoval();
				break;
			case 2:
				this->player->weaponCount["laserUse"] += Ammo->getAmmoMax();
				Ammo->markForRemoval();
				break;
			case 3:
				this->player->weaponCount["shieldUse"] += Ammo->getAmmoMax();
				Ammo->markForRemoval();
				break;
			case 4:
				this->player->weaponCount["bombeUse"] += Ammo->getAmmoMax();
				Ammo->markForRemoval();
				break;
			}
		}
	}
}


//fonction pour changer de niveau

void Game::updateLevel() {
	startTimeElapsed = startClock.getElapsedTime();


	if (startTimeElapsed.asSeconds() >= levelDuration) {
		if (currentLevel == 1) {
			startLevel(2); // Passer au niveau 2
		}
		else if (currentLevel == 2) {
			game_on = false; // Terminer le jeu après le niveau 2
		}
	}
}




//fonction pour mettre a jour les enemis

void Game::updateEnemy() {
	for (auto enemies : allEnemies) {
		enemies->updateSelf(window);

		// Gérer les attaques ennemies
		if (enemies->canAttack() && typeid(*enemies) != typeid (CloseRangeEnemy)) {
			this->allEnemyProjectiles.push_back(new Projectile(enemyProjectileTexture["boulet"],
				5.0f, 5.0f,
				enemies->getBounds().left ,
				(enemies->getBounds().top + (enemies->getBounds().height / 2)),
				-(enemies->getSpeed() + 10.f)
			));
		}

		// Collision joueur <-> ennemi
		if (enemies->getBounds().intersects(this->player->getBounds()) && !this->playerShield->active &&  typeid(*enemies) != typeid (Boss_1)) {
			this->player->loseHp(enemies->getDamage());
			cout << this->player->getHp()<<endl;
			enemies->markForRemoval();
		}
		else if (enemies->getBounds().intersects(this->player->getBounds()) && this->playerShield->active && typeid(*enemies) != typeid (Boss_1)) {
			enemies->markForRemoval();
		}
		if (enemies->getBounds().intersects(this->player->getBounds()) && typeid(*enemies) == typeid (Boss_1)) {
			this->player->loseHp(enemies->getDamage());
		}
		else if (enemies->getBounds().intersects(this->player->getBounds()) && this->playerShield->active && typeid(*enemies) == typeid (Boss_1)) {

		}
		

		// Collision projectiles joueur <-> ennemi
		for (auto projectiles = this->allPlayerProjectiles.begin(); projectiles != this->allPlayerProjectiles.end(); ++projectiles) {
			if ((*projectiles)->getBounds().intersects(enemies->getBounds())) {
				enemies->setHealth(enemies->getHealth() - this->player->getDamage());
				(*projectiles)->markForRemoval();

				if (enemies->getHealth() <= 0) {
					enemies->markForRemoval();
					this->score += 10;
				}
			}
		}
		if (enemies->isMarkedForRemoval()) {
			int spawnAmmo = rand() % 4;
			int randomShield = rand() % 100;
			int randomLaser = rand() % 100;
			int randomMissile = rand() % 100;
			int randomBomb = rand() % 100;
			switch (spawnAmmo) {
			case 0:
				
				if (randomShield < 10) {
					this->allAmmo.push_back(new Ammunition(AmmoTexture["bouclierMunition"], 1.0f, 1.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 1));
				}
			case 1:
				
				if (randomLaser < 10) {
					this->allAmmo.push_back(new Ammunition(AmmoTexture["missileMunition"], 1.0f, 1.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 2));

				}
			case 2:
				
				if (randomMissile < 10) {
					this->allAmmo.push_back(new Ammunition(AmmoTexture["bombeMunition"], 1.0f, 1.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 3));

				}
			case 3:
				
				if (randomBomb < 10) {
					this->allAmmo.push_back(new Ammunition(AmmoTexture["laserMunition"], 1.0f, 1.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 4));

				}
			}
		}
	}
}



//fonction pour mettre a jour les projectiles

void Game::updateProjectile()
{
}

			// Si un ennemi le plus proche est trouvé, mettre à jour le missile
			if (closestEnemy) {
				projectiles->updateSelf(closestEnemy->getSprite());
			}
			else 
			{
				projectiles->updateSelf(Sprite());
			}
		}
	}

	
	for (auto enemyProjectile : allEnemyProjectiles) {
		if (typeid(*enemyProjectile) == typeid(Projectile)) {
			enemyProjectile->updateSelf();

			if (enemyProjectile->getBounds().left + enemyProjectile->getBounds().width > window->getSize().x) {
				enemyProjectile->markForRemoval();
			}
			else if (enemyProjectile->getBounds().left + enemyProjectile->getBounds().width < 0.f) {
				enemyProjectile->markForRemoval();
			}

		}
	}

}


//fonction pour mettre a jour le joueur et ses armes

void Game::updatePlayer()
{	
	this->playerLaser->followPlayer(this->player->getSprite());
	this->playerShield->followPlayer(this->player->getSprite());
	this->player->update(window);
	if (this->player->getHp() <= 0) {

	}
}



//fonction qui lance toute les fonctions de mises a jour du statut du jeu

void Game::update() {
	
	this->updateAmmo();
	
	this->updatePlayer();

	this->spawnEnemy();

	this->updateInput();

	this->updateProjectile();

	this->updateEnemy();

	this->updateLevel();
	
	this->updateBoss();

	this->deleteObjects();
	

}


//-------------------------------------------------------------------------------------
//Fonction Render----------------------------------------------------------------------
//-------------------------------------------------------------------------------------


//fonction pour afficher tout le jeu
void Game::render()
{
	window->clear(Color::White);


	this->player->render(*window);

	
	
	for (auto* it : this->allPlayerProjectiles)
	{

		it->renderProjectile(window);
		
	}
	for (auto* it : this->allEnemyProjectiles)
	{
		it->renderProjectile(window);
	}

	for (auto* it : this->allEnemies)
	{

		it->renderEnemy(window);
	}
	
	for (auto* it : this->allAmmo)
	{

		it->renderAmmo(window);
	}

	this->playerLaser->renderProjectile(window);
	this->playerShield->renderProjectile(window);

	window->display();
}


