#include "Game.h"


Game::Game()
{
	this->window = new RenderWindow(VideoMode(1920, 1080), "Steam Purgator");
	this->window->setFramerateLimit(60);
	this->enemySpawnInterval = 4;
	srand(static_cast<unsigned int>(time(nullptr)));

	this->initPlayer();
	this->initProjectile();
	this->initEnemy();


	this->score = 0;
}

Game::~Game()
{
	delete this->window;
}



//-------------------------------------------------------------------------------------
//Fonction Init------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

void Game::initPlayer()
{
	this->player = make_unique<Player>(100,100,1.0f,1.0f,500,500,false,10.f, "asset/Perso stu.png");
}

void Game::initProjectile()
{
	this->playerProjectileTexture = new Texture;
	string imagePath = "asset/boulet de canon.png";
	if (!this->playerProjectileTexture->loadFromFile("asset/boulet de canon.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}
	else {
		std::cout << "Texture loaded successfully: " << imagePath << std::endl;
	}

}

void Game::initEnemy()
{
	cout << "test";
	enemyTextures["ranged"] = new Texture;
	if (!enemyTextures["ranged"]->loadFromFile("asset/Avion.png"))
	{
		cout << "ERROR::ENEMY::INITTEXTURE::Could not load Ranged enemy texture." << endl;
	}

	enemyTextures["close"] = new Texture;
	if (!enemyTextures["close"]->loadFromFile("asset/gargouille.png"))
	{
		cout << "ERROR::ENEMY::INITTEXTURE::Could not load Close Range enemy texture." << endl;
	}

	enemyTextures["big"] = new Texture;
	if (!enemyTextures["big"]->loadFromFile("asset/Dirigeable ennemie.png"))
	{
		cout << "ERROR::ENEMY::INITTEXTURE::Could not load Big enemy texture." << endl;
	}
}


/*void Game::spawnEnemy() {
	deltaTimeElasped = deltaClock.getElapsedTime();

	if (deltaTimeElasped.asSeconds() >= 2.0f) { // Temps entre deux spawns
		deltaClock.restart();

		// Définir les types d'ennemis avec leurs poids
		std::vector<std::pair<std::function<BigEnemy* ()>, int>> enemyTypes = {
			{ [this]() { return new RangedEnemy(this->enemyTexture, 1.5f, 1.5f, window->getSize().x, rand() % window->getSize().y, false, 10.f); }, 60 },
			{ [this]() { return new CloseRangeEnemy(this->enemyTexture, 2.0f, 2.0f, window->getSize().x, rand() % window->getSize().y, false, 0.05f, this->player->getPos()); }, 30 },
			{ [this]() { return new BigEnemy(this->enemyTexture, 3.0f, 3.0f, window->getSize().x, rand() % window->getSize().y, false, 0.03f, 1.5f); }, 10 }
		};

		// Calculer un ennemi à partir des probabilités
		int totalWeight = 0;
		for (const auto& enemyType : enemyTypes) {
			totalWeight += enemyType.second;
		}

		int randomWeight = rand() % totalWeight;
		BigEnemy* spawnedEnemy = nullptr;

		for (const auto& enemyType : enemyTypes) {
			if (randomWeight < enemyType.second) {
				spawnedEnemy = enemyType.first();
				break;
			}
			randomWeight -= enemyType.second;
		}

		if (spawnedEnemy) {
			this->allEnemies.push_back(spawnedEnemy);
			count++;
		}
	}
}*/
void Game::spawnEnemy()
{
	deltaTimeElasped = deltaClock.getElapsedTime();
	this->startTimeElapsed = this->startClock.getElapsedTime();
	if (deltaTimeElasped.asSeconds() >= enemySpawnInterval) {
		deltaClock.restart();

		int enemyX = window->getSize().x ;
		int enemyY = rand() % window->getSize().y;

		int enemyType = -1;
		int randomWeight = rand() % 100;



		if (randomWeight < 90) {
			if (this->startTimeElapsed.asSeconds() >= 5) {
				enemyType = 0;
			}
		}

		if (randomWeight < 60) {
			if (this->startTimeElapsed.asSeconds() >= 15) {
				enemyType = 1;
			}
		}
		

		if (randomWeight < 10) {
			if (this->startTimeElapsed.asSeconds() >= 20) {
				enemyType = 2;
			}
		}
		


		Texture* selectedTexture = nullptr;
		switch (enemyType) {
		case 0:
			selectedTexture = enemyTextures["close"];
			break;
		case 1:
			selectedTexture = enemyTextures["ranged"];
			break;
		case 2:
			selectedTexture = enemyTextures["big"];
			break;
		default:
			std::cerr << "Unknown enemy type!" << std::endl;
			break;
		}

		if (selectedTexture) {
			switch (enemyType) {
			case 0:
				this->allEnemies.push_back(new CloseRangeEnemy(
					selectedTexture, 2.0f, 2.0f, enemyX, enemyY, false, 10.f, this->player->getPos()
				));
				break;
			case 1:
				this->allEnemies.push_back(new RangedEnemy(
					selectedTexture, 1.5f, 1.5f, enemyX, enemyY, false, 10.f
				));
				break;
			
			case 2:
				this->allEnemies.push_back(new BigEnemy(
					selectedTexture, 3.0f, 3.0f, enemyX, enemyY, false, 10.f, 1.5f
				));
				break;
			}
		}

		std::cout << "Enemy spawned successfully!" << std::endl;
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
		this->levelDuration = 60; // Durée du niveau 1 (en secondes)
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
	this->player->movement(window);

	if (this->player->attack() == 1 && this->player->canAttack()) 
	{
		this->allPlayerProjectiles.push_back(new Projectile(playerProjectileTexture,
			20.0f,
			20.0f,
			this->player->getBounds().left + this->player->getBounds().width,
			this->player->getBounds().top + (this->player->getBounds().height / 2),
			false,
			1.f + this->player->getSpeed()
		)
		);
	}

	if (this->player->attack() == 2) {

	}
	if (this->player->attack() == 3) {

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
			this->allEnemyProjectiles.push_back(new Projectile(playerProjectileTexture,
				20.0f,
				20.0f,
				(*enemies)->getBounds().left + (*enemies)->getBounds().width,
				(*enemies)->getBounds().top + ((*enemies)->getBounds().height / 2),
				false,
				( (-(*enemies)->getSpeed() - 10.f))
			)
			);
		}

		for (auto projectiles = this->allPlayerProjectiles.begin(); projectiles != this->allPlayerProjectiles.end();) {

			if ((*projectiles)->getBounds().intersects((*enemies)->getBounds())) {
				delete* enemies;
				enemies = this->allEnemies.erase(enemies); 

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
		(*it)->updateSelf();

		if ((*it)->getBounds().left + (*it)->getBounds().width > window->getSize().x) {
			delete* it; 
			it = this->allPlayerProjectiles.erase(it); 
		}
		else {
			++it; 
		}
	}
	for (auto it = this->allEnemyProjectiles.begin(); it != this->allEnemyProjectiles.end();) {
		(*it)->updateSelf();

		if ((*it)->getBounds().left + (*it)->getBounds().width < 0.f) {
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


