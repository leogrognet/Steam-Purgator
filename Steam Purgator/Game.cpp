#include "Game.h"


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

	this->currentWeapon = 0;

	this->initPlayer();
	this->initAmmo();
	this->initProjectile();
	this->initEnemy();
	this->initBG();

	this->score = 0;
}

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

void Game::loadTexture(map<String, Texture*>& textureMap, const string& key, const string& path)
{
	textureMap[key] = new Texture;
	if (!textureMap[key]->loadFromFile(path)) {
		cout << "ERROR::Could not load texture: " << path << endl;
	}

}

void Game::initPlayer()
{
	this->player = make_unique<Player>(100,100,1.0f,1.0f,500,500,false,10.f, "asset/SpriteAsset/Perso stu.png",54,30,54,30 );

}

void Game::initAmmo()
{

	this->loadTexture(this->AmmoTexture,"bombeMunition", "asset/SpriteAsset/mun Bombe.png");
	this->loadTexture(this->AmmoTexture, "laserMunition", "asset/SpriteAsset/mun laser.png");
	this->loadTexture(this->AmmoTexture, "missileMunition", "asset/SpriteAsset/mun missile.png");
	this->loadTexture(this->AmmoTexture, "bouclierMunition", "asset/SpriteAsset/mun bouclier.png");

	if (this->AmmoTexture["bombeMunition"] == nullptr) {
		cout << "oui" << endl ;
	}
}



void Game::initProjectile()
{
	this->loadTexture(this->playerProjectileTexture, "boulet", "asset/SpriteAsset/boulet de canon.png");
	this->loadTexture(this->playerProjectileTexture, "laser", "asset/SpriteAsset/laser.png");
	this->loadTexture(this->playerProjectileTexture, "missile", "asset/SpriteAsset/missile.png");
	this->loadTexture(this->playerProjectileTexture, "bouclier", "asset/SpriteAsset/bouclier.png");
	this->loadTexture(this->playerProjectileTexture, "bombe", "asset/SpriteAsset/Bombe.png");



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
		std::cerr << "Level not implemented!" << std::endl;
		break;
	}
}




//-------------------------------------------------------------------------------------
//Fonction Run-------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

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

void Game::updateInput()
{
	
	if (this->player->attack() == 1 && this->player->canAttack()) 
	{
		//cout << "test";
		this->allPlayerProjectiles.push_back(new Projectile(playerProjectileTexture["boulet"],
			5.0f,
			5.0f,
			this->player->getBounds().left + this->player->getBounds().width,
			this->player->getBounds().top + (this->player->getBounds().height / 2),
			false,
			1.f + this->player->getSpeed()
		)
		);
	}

	if (this->player->attack() == 2 && player->canAttack()) {
		
		switch (currentWeapon) {
			cout << currentWeapon << endl;
		case 0:
			this->allPlayerProjectiles.push_back(new Missile(playerProjectileTexture["missile"], 1.0f, 1.0f, this->player->getSprite().getPosition().x, this->player->getSprite().getPosition().y, false, 1.0f));
			break;
		case 1:
			if (this->player->weaponCount["laserUse"] > 0) {

			}
			break;
		case 2:
			if (this->player->weaponCount["shieldUse"] > 0) {
				
			}
			break;
		case 3:
			if (this->player->weaponCount["bombUse"] > 0) {

			}
			break;
		}
	}
	if (this->player->attack() == 3 && player->canAttack()) {
		currentWeapon++;
		cout << currentWeapon << endl;
		if (currentWeapon > 3) {
			currentWeapon = 0;
		}
	}
	
}








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



void Game::updateEnemy()
{

	for (auto enemies = this->allEnemies.begin(); enemies != this->allEnemies.end();) {
		(*enemies)->updateSelf(window);
		if ((*enemies)->canAttack() &&  dynamic_cast<CloseRangeEnemy*> (*enemies) == nullptr) {
			
			this->allEnemyProjectiles.push_back(new Projectile(enemyProjectileTexture["boulet"],
				5.0f,
				5.0f,
				(*enemies)->getBounds().left + (*enemies)->getBounds().width,
				(*enemies)->getBounds().top + ((*enemies)->getBounds().height / 2),
				false,
				( (-(*enemies)->getSpeed() - 10.f))
			)
			);
			
			for (auto enemyProjectiles = this->allEnemyProjectiles.begin(); enemyProjectiles != this->allEnemyProjectiles.end();) {
				if ((*enemyProjectiles)->getBounds().intersects(this->player->getBounds())) {
					this->player->loseHp((*enemies)->getDamage());
					cout << this->player->getHp();
					delete* enemyProjectiles;
					enemyProjectiles = this->allEnemyProjectiles.erase(enemyProjectiles);
				}
				else {
					++enemyProjectiles;
				}
			}
		}
			
		if ((*enemies)->getBounds().intersects(this->player->getBounds())) {
				this->player->loseHp((*enemies)->getDamage());
				cout << this->player->getHp();
				delete* enemies;
				enemies = this->allEnemies.erase(enemies);
		}
		
		


		for (auto projectiles = this->allPlayerProjectiles.begin(); projectiles != this->allPlayerProjectiles.end();) {

			if ((*projectiles)->getBounds().intersects((*enemies)->getBounds())) {
				(*enemies)->setHealth((*enemies)->getHealth() - this->player->getDamage());
				if ((*enemies)->getHealth() <= 0) {
					delete* enemies;
					enemies = this->allEnemies.erase(enemies);
				}
				delete* projectiles;
				projectiles = this->allPlayerProjectiles.erase(projectiles); 

				this->score += 10;
			}
			else {
				++projectiles; 
			}
		}

		if (enemies != this->allEnemies.end()) {
			++enemies;
		}
	}
	


}

void Game::updateProjectile()
{
	for (auto it = this->allPlayerProjectiles.begin(); it != this->allPlayerProjectiles.end();) {
		if (typeid(**it) == typeid(Projectile)) {
			(*it)->updateSelf();


			if ((*it)->getBounds().left + (*it)->getBounds().width > window->getSize().x) {
				delete* it;
				it = this->allPlayerProjectiles.erase(it);
			}
			else if ((*it)->getBounds().left + (*it)->getBounds().width < 0.f) {
				delete* it;
				it = this->allPlayerProjectiles.erase(it);
			}
		}

		else if (dynamic_cast<Laser*> (*it) != nullptr) {
			for (auto enemies = this->allEnemies.begin(); enemies != this->allEnemies.end();) {
			
				if ((*it)->getBounds().intersects((*enemies)->getSprite().getGlobalBounds())) {
					//(*it)->getSprite().setTextureRect((*it)->getSprite().getTextureRect().width()-(*enemies)->getSprite().getGlobalBounds().left,);
				}
			}
		}
		else if(dynamic_cast<Missile*> (*it) != nullptr ){
			//for (auto enemies = this->allEnemies.begin(); enemies != this->allEnemies.end();) {
				//(*it)->updateSelf((*enemies)->getSprite());
			//}
		}
		else {
			++it;
		}
	}
	for (auto it = this->allEnemyProjectiles.begin(); it != this->allEnemyProjectiles.end();) {
		if (dynamic_cast<Projectile*> (*it) != nullptr) {
			(*it)->updateSelf();
		}
		if ((*it)->getBounds().left + (*it)->getBounds().width > window->getSize().x && dynamic_cast<Shield*> (*it) == nullptr && dynamic_cast<Laser*> (*it) == nullptr) {
			delete* it;
			it = this->allEnemyProjectiles.erase(it);
		}
		else if ((*it)->getBounds().left + (*it)->getBounds().width < 0.f && dynamic_cast<Shield*> (*it) == nullptr && dynamic_cast<Laser*> (*it) == nullptr) {
			delete* it;
			it = this->allEnemyProjectiles.erase(it);
		}
		else {
			++it;
		}
	}

}

void Game::updatePlayer()
{	
	this->player->update(window);
	if (this->player->getHp() <= 0) {

	}
}

void Game::update() {
	

	


	this->updatePlayer();

	this->spawnEnemy();

	this->updateInput();

	this->updateProjectile();

	this->updateEnemy();

	this->updateLevel();

	

}


//-------------------------------------------------------------------------------------
//Fonction Render----------------------------------------------------------------------
//-------------------------------------------------------------------------------------

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
	
	window->display();
}


