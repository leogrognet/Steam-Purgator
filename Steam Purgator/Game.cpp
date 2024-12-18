#include "Game.h"

// constructeur de game

Game::Game()
{
	
	this->enemySpawnInterval = 0.5f;
	srand(static_cast<unsigned int>(time(nullptr)));

	this->animP = Vector2f(1, 0);
	this->animG = Vector2f(1, 0);
	this->animB = Vector2f(1, 0);
	this->animD = Vector2f(1, 0);

	this->animTourmap = Vector2f(0, 0);

	this->isBossKilled = false;
	this->score = 0;
	this->currentWeapon = 1;


 
}



//destructeur de game vidant la memoire 
Game::~Game()
{


	
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

		delete it->second;  // Libère le pointeur Texture*

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



//fonction qui pemet de creer une nouvelle texture avec une image

void Game::loadTexture(map<String, Texture*>& textureMap, const string& key, const string& path)
{
	textureMap[key] = new Texture;
	if (!textureMap[key]->loadFromFile(path)) {
		cout << "ERROR::Could not load texture: " << path << endl;
	}

}



//initie le joueur et sa texture

void Game::initPlayer()
{
	this->loadTexture(this->playerTextures, "barreVie", "asset/SpriteAsset/barre_de_vie.png");
	this->loadTexture(this->playerTextures, "perso", "asset/SpriteAsset/Perso stu.png");
	this->loadTexture(this->playerTextures, "NbMissile", "asset/SpriteAsset/NbMissile.png");
	this->loadTexture(this->playerTextures, "NbLaser", "asset/SpriteAsset/Nblaser.png");
	this->loadTexture(this->playerTextures, "NbBouclier", "asset/SpriteAsset/NbBouclier.png");
	this->loadTexture(this->playerTextures, "NbBombe", "asset/SpriteAsset/NbBombe.png");
	this->player = make_unique<Player>(playerTextures["perso"],playerTextures["barreVie"], playerTextures["NbMissile"], playerTextures["NbLaser"], playerTextures["NbBouclier"], playerTextures["NbBombe"], 200, 2.0f, 2.0f, 500, 500, 10.f, 54, 30, 54, 30);


}


//initie les textures des munitions

void Game::initAmmo()
{

	this->loadTexture(this->AmmoTexture,"bombeMunition", "asset/SpriteAsset/mun Bombe.png");
	this->loadTexture(this->AmmoTexture, "laserMunition", "asset/SpriteAsset/mun laser.png");
	this->loadTexture(this->AmmoTexture, "missileMunition", "asset/SpriteAsset/mun missile.png");
	this->loadTexture(this->AmmoTexture, "bouclierMunition", "asset/SpriteAsset/mun bouclier.png");

}




//initie les textures des projectiles

void Game::initProjectile()
{
	this->loadTexture(this->playerProjectileTexture, "boulet", "asset/SpriteAsset/boulet de canon.png");
	this->loadTexture(this->playerProjectileTexture, "laser", "asset/SpriteAsset/laser.png");
	this->loadTexture(this->playerProjectileTexture, "missile", "asset/SpriteAsset/missile.png");
	this->loadTexture(this->playerProjectileTexture, "bouclier", "asset/SpriteAsset/bouclier.png");
	this->loadTexture(this->playerProjectileTexture, "bombe", "asset/SpriteAsset/Bombe.png");
	this->playerLaser = make_unique<Laser>(playerProjectileTexture["laser"], 1.0f, 1.0f, this->player->getPos().x + this->player->getBounds().width, this->player->getPos().y + this->player->getBounds().height / 2,this->player->getSprite(),3.0f);
	this->playerShield = make_unique<Shield>(playerProjectileTexture["bouclier"], 1.0f, 1.0f, this->player->getPos().x + this->player->getBounds().width, this->player->getPos().y + this->player->getBounds().height / 2);

	//Texture pour l'ennemi

	this->loadTexture(this->enemyProjectileTexture, "boulet", "asset/SpriteAsset/boulet de canon.png");
	this->loadTexture(this->enemyProjectileTexture, "bombe", "asset/SpriteAsset/Bombe.png");
	this->loadTexture(this->enemyProjectileTexture, "flame", "asset/SpriteAsset/flame.png");
}



//inities les textures des ennemis

void Game::initEnemy()
{
	this->loadTexture(this->enemyTextures, "Avion", "asset/SpriteAsset/Avion.png");
	this->loadTexture(this->enemyTextures, "Gargouille", "asset/SpriteAsset/gargouille.png");
	this->loadTexture(this->enemyTextures, "Dirigeable Ennemi", "asset/SpriteAsset/Dirigeable ennemie.png");
	this->loadTexture(this->enemyTextures, "Boss_1", "asset/SpriteAsset/Boss.png");
	
}

//inititie l'arriere plan
void Game::initBG()
{
	this->loadTexture(this->BackGroundTexture, "Tour", "asset/SpriteAsset/Tour.png");
	this->loadTexture(this->BackGroundTexture, "1stMapVide", "asset/SpriteAsset/Map vide2.png");
	this->loadTexture(this->BackGroundTexture, "Nuage1", "asset/SpriteAsset/nuage.png");
	this->loadTexture(this->BackGroundTexture, "Nuage2", "asset/SpriteAsset/nuage lv 2.png");
	this->loadTexture(this->BackGroundTexture, "BG1", "asset/SpriteAsset/BackGround back.png");
	this->loadTexture(this->BackGroundTexture, "BG2", "asset/SpriteAsset/BackGround back.png");
	this->levelBG = make_unique<setBG>(this->BackGroundTexture["Tour"], this->BackGroundTexture["1stMapVide"], this->BackGroundTexture["Nuage1"], this->BackGroundTexture["Nuage2"], this->BackGroundTexture["BG1"], this->BackGroundTexture["BG2"],window);

}

void Game::initScoreText()
{
	this->loadScoreFont();
	ScoreText.setFont(this->font);
	ScoreText.setCharacterSize(50);
	ScoreText.setFillColor(Color::Black);
	ScoreText.setStyle(Text::Regular);
	ScoreText.setPosition(window->getSize().x-500, 50);
	ScoreText.setString("0");
	String Score(to_string(this->score));
	ScoreText.setString("Score:"+Score);


}


int Game::loadScoreFont()
{
	if (!font.loadFromFile("asset/textAsset/Crang.ttf")) {
		return -1;
	}
}

void Game::allinit()
{
	this->initScoreText();
	this->initPlayer();
	this->initAmmo();
	this->initProjectile();
	this->initEnemy();
	this->initBG();
}




//detruit un objet d'une liste

void Game::deleteObjects() {
	// Nettoyer les ennemis
	for (auto scoreAdds : this->allEnemies) {
		if (typeid (scoreAdds) == typeid(CloseRangeEnemy) && scoreAdds->isMarkedForRemoval()) {
			this->score += 10;
		}
		if (typeid (scoreAdds) == typeid(BigEnemy) && scoreAdds->isMarkedForRemoval()) {
			this->score += 150;
		}
		if (typeid (scoreAdds) == typeid(RangedEnemy) && scoreAdds->isMarkedForRemoval()) {
			this->score += 200;
		}
	}
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




//fonction pour faire spawn les ennemis aleatoirement

void Game::spawnEnemy()
{

	if (this->canSpawn) {
		//cout << "test" << endl;
		deltaTimeElasped = deltaClock.getElapsedTime();
		this->startTimeElapsed = this->startClock.getElapsedTime();




		int min = 200;
		int max = window->getSize().y - min;

		int enemyX = window->getSize().x;
		int enemyY = min + rand() % (max - min + 1);

		int maxEnemies = 30; 
		if (this->allEnemies.size() >= maxEnemies) {
			return; // Ne pas spawner d'ennemis si on atteint la limite
		}

		float baseInterval = 2.5f; 
		float minInterval = 0.5f;  
		float timeScaleFactor = 0.01f; 

		this->enemySpawnInterval = std::max(minInterval, baseInterval - (timeScaleFactor * startTimeElapsed.asSeconds()));


		int randomWeight = rand() % 100;


		if (randomWeight < 100) {
			if (this->startTimeElapsed.asSeconds() >= 0) {
				if (deltaTimeElasped.asSeconds() >= enemySpawnInterval) {
					this->enemy1 = true;
					deltaClock.restart();
				}
			}
		}

		if (randomWeight > 70) {
			if (this->startTimeElapsed.asSeconds() >= 10) {
				if (deltaTimeElasped.asSeconds() >= enemySpawnInterval) {
					this->enemy2 = true;
					deltaClock.restart();
				}
			}
		}


		if (randomWeight < 10) {
			if (this->startTimeElapsed.asSeconds() >= 20) {
				if (deltaTimeElasped.asSeconds() >= enemySpawnInterval) {
					this->enemy3 = true;
					deltaClock.restart();
				}
			}
		}


		Texture* selectedTexture = nullptr;

		if (enemy1) {
			this->allEnemies.push_back(new CloseRangeEnemy(

				enemyTextures["Gargouille"], 2.0f, 2.0f, enemyX, enemyY, false, 10.f, this->player->getPos(),
				100, 100, 100, 100
			));
			enemy1 = false;
		}
		if (enemy2) {

			this->allEnemies.push_back(new RangedEnemy(
				enemyTextures["Avion"], 1.5f, 1.5f, enemyX, enemyY, false, 10.f
			));
			enemy2 = false;
		}
		if (enemy3) {
			this->allEnemies.push_back(new BigEnemy(
				enemyTextures["Dirigeable Ennemi"], 3.0f, 3.0f, enemyX, enemyY, false, 10.f, 1.5f,
				47, 31, 47, 31
			));
			enemy3 = false;
		}
	}
}



//fonction de spwan du boss

void Game::spawnBoss()
{
	this->allEnemies.push_back(new Boss_1(enemyTextures["Boss_1"], 2.0f, 2.0f, window->getSize().x - 300, window->getSize().y / 2 -200, true, 1.0f, 274, 273, 274, 273));
}






//fonction pour configurer les niveau

void Game::startLevel(int level) {
	this->currentLevel = level;
	this->allEnemies.clear();  // Nettoyer les ennemis existants
	this->allPlayerProjectiles.clear();
	this->allEnemyProjectiles.clear();

	// Configurer des paramètres spécifiques au niveau
	switch (level) {
	case 1:
		this->levelDuration = 300; // Durée du niveau 1 (en secondes)
		this->enemySpawnInterval = 2;// Temps entre les spawns d'ennemis
		break;
	case 2:
		this->levelDuration = 420; // Durée du niveau 2 (en secondes)
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
	this->startLevel(1);
	this->window = new RenderWindow(VideoMode(1920, 1080), "Steam Purgator");
	this->window->setFramerateLimit(60);

	this->allinit();

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


//fonction pour mettre a jour les input du joueur et les interactions de ses input

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
				1.f + this->player->getSpeed(),10
			)
			);
	}
	if (this->player->attack() == 2) { 
		switch (currentWeapon) {
		case 1:
			if (this->player->canAttack() && this->player->weaponCount["missileUse"] > 0) {
				this->allPlayerProjectiles.push_back(new Missile(playerProjectileTexture["missile"], 1.0f, 1.0f, this->player->getSprite().getPosition().x, this->player->getSprite().getPosition().y, 1.f + this->player->getSpeed(), 63, 21, 63, 21,20.f));
				this->player->weaponCount["missileUse"] -= 1;
				cout << this->player->weaponCount["missileUse"] << endl;
			}
			break;
		case 2:
			if (this->player->weaponCount["laserUse"] > 0){
				this->playerLaser->setActive(true);
				this->player->weaponCount["laserUse"] -= 1;
			}
			break;

		case 3:
			if (this->player->weaponCount["shieldUse"] > 0) {
				this->playerShield->setActive(true);
				this->player->weaponCount["shieldUse"] -= 1;
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
			if (currentWeapon > 3) {
				currentWeapon = 1;
			}
			
		}

	}
}








//fonction de mise a jour du boss

void Game::updateBoss()
{
	for (auto boss : allEnemies) {
		Boss_1* boss1 = dynamic_cast<Boss_1*>(boss);

		if (boss1) { // Si le cast est réussi, boss est un Boss_1
			cout << boss1->getHealth()<<endl;
				boss1->updateSelf(window);
				if (boss1->deltaAttackTime.asSeconds() > 1 && boss1->isShooting) {
					
					
					int angle = 180;
					int speedFire = 4.0f;
					this->allEnemyProjectiles.push_back(new FlameBall(enemyProjectileTexture["flame"], 5.0f, 5.0f, boss1->getPos().x + 20, boss1->getPos().y + 150, speedFire, angle, 20));
					this->allEnemyProjectiles.push_back(new FlameBall(enemyProjectileTexture["flame"], 5.0f, 5.0f, boss1->getPos().x + 20, boss1->getPos().y + 150, speedFire, angle - 20, 20));
					this->allEnemyProjectiles.push_back(new FlameBall(enemyProjectileTexture["flame"], 5.0f, 5.0f, boss1->getPos().x + 20, boss1->getPos().y + 150, speedFire, angle - 40,20));
					this->allEnemyProjectiles.push_back(new FlameBall(enemyProjectileTexture["flame"], 5.0f, 5.0f, boss1->getPos().x + 20, boss1->getPos().y + 150, speedFire, angle + 20,20));
					this->allEnemyProjectiles.push_back(new FlameBall(enemyProjectileTexture["flame"], 5.0f, 5.0f, boss1->getPos().x + 20, boss1->getPos().y + 150, speedFire, angle + 40,20));
					boss1->deltaAttack.restart();
				}
			



			if (boss1->getHealth() < 0) {
				this->isBossKilled = true;
				boss1->markForRemoval();
			}

			// Gérer les collisions
			if (boss1->getBounds().intersects(this->player->getBounds())) {
				if (this->playerShield->active) {
					this->player->setHp(this->player->getHp());
				}
				else {
					this->player->loseHp(10);
				}
			}
		}
		
		if (this->isBossKilled) {
				boss->markForRemoval();
			}
	}
}



//fonction de mise a jour des munitions

void Game::updateAmmo()
{
	for (auto Ammo : allAmmo) {
		Ammo->updateSelf();
		if (Ammo->sprite.getPosition().y > window->getSize().y) {
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



//fonction qui passe dun niveau a un autre
void Game::updateLevel() {
	startTimeElapsed = startClock.getElapsedTime();
	if (startTimeElapsed.asSeconds() < levelDuration && currentLevel == 1) {
		this->canSpawn = true;
		spawnEnemy();
	}
	if (startTimeElapsed.asSeconds() >= levelDuration && this->allEnemies.empty() && currentLevel == 1) {
		this->canSpawn = false;
		spawnBoss();
	}
	if (startTimeElapsed.asSeconds() >= levelDuration + 5 && this->allEnemies.empty() && isBossKilled && currentLevel == 1){
		startLevel(2);
		this->isBossKilled = false;
	}

}





//fonction pour mettre a jour les annemis

void Game::updateEnemy() {
	for (auto enemies : allEnemies) {
		enemies->updateSelf(window);


		// Gérer les attaques ennemies
		if (enemies->canAttack() && typeid(*enemies) != typeid (CloseRangeEnemy) && typeid(*enemies) != typeid (Boss_1)) {
			this->allEnemyProjectiles.push_back(new Projectile(enemyProjectileTexture["boulet"],
				5.0f, 5.0f,
				enemies->getBounds().left ,
				(enemies->getBounds().top + (enemies->getBounds().height / 2)),
				-(enemies->getSpeed() + 10.f),enemies->getDamage()
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
		if (enemies->sprite.getGlobalBounds().width + enemies->sprite.getPosition().x < 0) {
			enemies->markForRemoval();
		}
		if (enemies->getHealth() <= 0) {
			enemies->markForRemoval();
		}

		// Collision projectiles joueur <-> ennemi
		for (auto projectiles = this->allPlayerProjectiles.begin(); projectiles != this->allPlayerProjectiles.end(); ++projectiles) {
			if ((*projectiles)->getBounds().intersects(enemies->getBounds())) {
				enemies->setHealth(enemies->getHealth() - (*projectiles)->getDamage());
				(*projectiles)->markForRemoval();

			}
		}
		if (this->playerLaser->getSprite().getGlobalBounds().intersects(enemies->getBounds())  && this->playerLaser->active) {
			enemies->setHealth(enemies->getHealth() - this->playerLaser->getDamage());
		}
		if (enemies->isMarkedForRemoval()) {
			int spawnAmmo = rand() % 3;
			int randomShield = rand() % 100;
			int randomLaser = rand() % 100;
			int randomMissile = rand() % 100;
			int randomBomb = rand() % 100;
			this->score += enemies->enemyScorePoints;
			switch (spawnAmmo) {
			case 0:
				
				if (randomShield < 10) {
					this->allAmmo.push_back(new Ammunition(AmmoTexture["missileMunition"], 1.0f, 1.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 1));
				}
			case 1:
				
				if (randomLaser < 10) {
					this->allAmmo.push_back(new Ammunition(AmmoTexture["laserMunition"], 2.0f, 2.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 2));

				}
			case 2:
				
				if (randomMissile < 10) {
					this->allAmmo.push_back(new Ammunition(AmmoTexture["bouclierMunition"], 1.0f, 1.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 3));

				}
			//case 3:
				
				//if (randomBomb < 10) {
					//this->allAmmo.push_back(new Ammunition(AmmoTexture["bombeMunition"], 1.0f, 1.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 4));

				//}
			}
		}
	}
}




//fonction de mise a jour des projectiles

void Game::updateProjectile()
{
	for (auto projectiles : allPlayerProjectiles) {
		if (typeid (*projectiles) == typeid (Projectile)) {
			projectiles->updateSelf();
			if (projectiles->getBounds().left + projectiles->getBounds().width > window->getSize().x) {
				projectiles->markForRemoval();
			}
			else if (projectiles->getBounds().left + projectiles->getBounds().width < 0.f) {
				projectiles->markForRemoval();
			}
		}
		else if (typeid(*projectiles) == typeid(Missile)) {
			// Trouver l'ennemi le plus proche
			BigEnemy* closestEnemy = nullptr;
			float closestDistance = numeric_limits<float>::max();

			for (auto enemy : allEnemies) {
				float distance = std::sqrt(
					pow(enemy->getSprite().getPosition().x - projectiles->getBounds().left, 2) +
					pow(enemy->getSprite().getPosition().y - projectiles->getBounds().top, 2));

					if (distance < closestDistance) {
						closestDistance = distance;
						closestEnemy = enemy;
					}
			}

			// Si un ennemi le plus proche est trouvé, mettre à jour le missile
			if (closestEnemy) {
				projectiles->updateSelf(closestEnemy->getSprite());
				projectiles->isClosest = true;
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
			else if (enemyProjectile->getBounds().intersects(this->player->getBounds())) {
				enemyProjectile->markForRemoval();
				this->player->loseHp(10);
			}

		}
		else if (typeid(*enemyProjectile) == typeid(FlameBall)) {
			FlameBall* flameball = dynamic_cast<FlameBall*>(enemyProjectile);
			if (flameball) {
				flameball->updateSelf();
				if (flameball->getBounds().intersects(this->player->getBounds())) {
					flameball->markForRemoval();
					this->player->loseHp(10);
				}
			}
			
		}
	}

}




//fonction de mise a jour de letat du joueur et de ses armes
void Game::updatePlayer()
{	
	this->playerLaser->followPlayer(this->player->getSprite());
	this->playerShield->followPlayer(this->player->getSprite());
	this->player->update(window);
	String Score(to_string(this->score));
	ScoreText.setString("Score:" + Score);
	if (this->player->getHp() <= 0) {

	}
}

void Game::updateBG()
{
	this->levelBG->updateScrolling(window);
}


//fonction qui utilise toute les mise a jour
void Game::update() {

	this->updateLevel();

	this->updateAmmo();
	
	this->updatePlayer();

	this->updateInput();

	this->updateProjectile();

	this->updateEnemy();

	this->updateBG();

	
	
	this->updateBoss();

	this->deleteObjects();
	

}


//-------------------------------------------------------------------------------------
//Fonction Render----------------------------------------------------------------------
//-------------------------------------------------------------------------------------




//fonctiuon daffichage du jeu

void Game::render()
{
	window->clear(Color::White);
	
	this->levelBG->renderBg(window);

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



	this->window->draw(this->ScoreText);


	this->playerLaser->renderProjectile(window);
	this->playerShield->renderProjectile(window);

	window->display();
}






