#include "Game.h"

// constructeur de game
Game::Game()
{
	this->window = new RenderWindow(VideoMode(1920, 1080), "Steam Purgator");
	this->window->setFramerateLimit(60);
	this->enemySpawnInterval = 1.f;
	srand(static_cast<unsigned int>(time(nullptr)));

	this->animP = Vector2f(1, 0);
	this->animG = Vector2f(1, 0);
	this->animB = Vector2f(1, 0);
	this->animD = Vector2f(1, 0);

	this->animTourmap = Vector2f(0, 0);

	this->isBossKilled = false;

	this->currentWeapon = 1;

	this->initPlayer();
	this->initAmmo();
	this->initProjectile();
	this->initEnemy();
	this->initBG();


	this->score = 0;
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
	this->player = make_unique<Player>(100,100,2.0f,2.0f,500,500,false,10.f, "asset/SpriteAsset/Perso stu.png",54,30,54,30 );

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
	this->playerLaser = make_unique<Laser>(playerProjectileTexture["laser"], 1.0f, 1.0f, this->player->getPos().x + this->player->getBounds().width, this->player->getPos().y + this->player->getBounds().height / 2,this->player->getSprite());
	this->playerShield = make_unique<Shield>(playerProjectileTexture["bouclier"], 1.0f, 1.0f, this->player->getPos().x + this->player->getBounds().width, this->player->getPos().y + this->player->getBounds().height / 2);

	//Texture pour l'ennemi

	this->loadTexture(this->enemyProjectileTexture, "boulet", "asset/SpriteAsset/boulet de canon.png");
	this->loadTexture(this->enemyProjectileTexture, "bombe", "asset/SpriteAsset/Bombe.png");
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
	this->loadTexture(this->BackGroundTexture, "1stMapVide", "asset/SpriteAsset/Map vide.png");

	this->levelBG = make_unique<setBG>(this->BackGroundTexture["Tour"], this->BackGroundTexture["1stMapVide"], 1.0f,1.0f,500.f, 384.f);

}


//detruit un objet d'une liste
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
					47, 31, 47, 31
				));
				break;
			}
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
		this->levelDuration = 30; // Durée du niveau 1 (en secondes)
		this->enemySpawnInterval = 3;// Temps entre les spawns d'ennemis
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








//fonction de mise a jour du boss
void Game::updateBoss()
{
	for (auto boss : allEnemies) {
		// Tenter de caster boss en Boss_1
		Boss_1* boss1 = dynamic_cast<Boss_1*>(boss);

		if (boss1) { // Si le cast est réussi, boss est un Boss_1
			int randomPattern = rand() % 20;

			if (randomPattern > 10) {
				boss1->firstPhase(true); // Appeler une fonction spécifique à Boss_1
			}

			boss1->updateSelf(window);
			if (boss1->getHealth() < 0) {
				this->isBossKilled = true;
			}

			// Gérer les collisions
			if (boss1->getBounds().intersects(this->player->getBounds())) {
				if (this->playerShield->active) {
					this->player->setHp(this->player->getHp());
				}
				else {
					this->player->loseHp(boss1->getDamage());
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

		}
	}

}



//fonction de mise a jour de letat du joueur et de ses armes
void Game::updatePlayer()
{	
	this->playerLaser->followPlayer(this->player->getSprite());
	this->playerShield->followPlayer(this->player->getSprite());
	this->player->update(window);
	if (this->player->getHp() <= 0) {

	}
}

void Game::updateBG()
{
	this->levelBG->animBG(window);

}


//fonction qui utilise toute les mise a jour
void Game::update() {

	this->updateLevel();

	this->updateAmmo();
	
	this->updatePlayer();

	this->updateInput();

	this->updateProjectile();

	this->updateEnemy();

	
	
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


	
	


	this->playerLaser->renderProjectile(window);
	this->playerShield->renderProjectile(window);

	window->display();
}






