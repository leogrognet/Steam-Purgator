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


	this->initPlayer();
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

void Game::initPlayer()
{
	this->player = make_unique<Player>(100,100,1.0f,1.0f,500,500,false,10.f, "asset/SpriteAsset/Perso stu.png");
}

void Game::initProjectile()
{
	//Texture pour le joueur

	this->playerProjectileTexture["boulet"] = new Texture;
	if (!this->playerProjectileTexture["boulet"]->loadFromFile("asset/SpriteAsset/boulet de canon.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}

	this->playerProjectileTexture["laser"] = new Texture;
	if (!this->playerProjectileTexture["laser"]->loadFromFile("asset/SpriteAsset/Laser.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}

	this->playerProjectileTexture["missile"] = new Texture;
	if (!this->playerProjectileTexture["missile"]->loadFromFile("asset/SpriteAsset/missile.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}

	this->playerProjectileTexture["bouclier"] = new Texture;
	if (!this->playerProjectileTexture["bouclier"]->loadFromFile("asset/SpriteAsset/Bouclier.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}

	this->playerProjectileTexture["bombe"] = new Texture;
	if (!this->playerProjectileTexture["bombe"]->loadFromFile("asset/SpriteAsset/Bombe.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}



	//Texture pour l'ennemi

	this->enemyProjectileTexture["boulet"] = new Texture;
	if (!this->enemyProjectileTexture["boulet"]->loadFromFile("asset/SpriteAsset/boulet de canon.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}

	this->enemyProjectileTexture["bombe"] = new Texture;
	if (!this->enemyProjectileTexture["bombe"]->loadFromFile("asset/SpriteAsset/bombe.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}

}

void Game::initEnemy()
{
	this->enemyTextures["Avion"] = new Texture;
	if (!enemyTextures["Avion"]->loadFromFile("asset/SpriteAsset/Avion.png"))
	{
		cout << "ERROR::ENEMY::INITTEXTURE::Could not load Avion enemy texture." << endl;
	}

	this->enemyTextures["Gargouille"] = new Texture;
	if (!enemyTextures["Gargouille"]->loadFromFile("asset/SpriteAsset/gargouille.png"))
	{
		cout << "ERROR::ENEMY::INITTEXTURE::Could not load Gargouille enemy texture." << endl;
	}

	this->enemyTextures["Dirigeable Ennemi"] = new Texture;
	if (!enemyTextures["Dirigeable Ennemi"]->loadFromFile("asset/SpriteAsset/Dirigeable ennemie.png"))
	{
		cout << "ERROR::ENEMY::INITTEXTURE::Could not load Dirigeable Ennemi texture." << endl;
	}
	this->enemyTextures["Boss_1"] = new Texture;
	if (!enemyTextures["Boss_1"]->loadFromFile("asset/SpriteAsset/Boss.png"))
	{
		cout << "ERROR::ENEMY::INITTEXTURE::Could not load Boss_1 texture." << endl;
	}

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
					
					selectedTexture, 2.0f, 2.0f, enemyX, enemyY, false, 10.f, this->player->getPos(), animG.x * 100, animG.y * 100, 100, 100
				));
				break;
			case 1:
				this->allEnemies.push_back(new RangedEnemy(
					selectedTexture, 1.5f, 1.5f, enemyX, enemyY, false, 10.f
				));
				break;
			
			case 2:
				this->allEnemies.push_back(new BigEnemy(
					selectedTexture, 3.0f, 3.0f, enemyX, enemyY, false, 10.f, 1.5f, animD.x * 47, animD.y * 31, 47, 31
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
	this->player->movement(window);

	if (this->player->attack() == 1 && this->player->canAttack()) 
	{
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

	if (this->player->attack() == 2) {

	}
	if (this->player->attack() == 3) {

	}
}


void Game::updateAnim() {
	static sf::Clock clock; // Horloge pour suivre le temps écoulé
	float elapsedTime = clock.restart().asSeconds(); // Temps écoulé depuis la dernière frame

	// Vitesse des animations (en secondes par frame)
	const float playerAnimSpeed = 0.1f;  // 10 FPS pour le joueur
	const float gargouilleAnimSpeed = 0.15f;  // 6.67 FPS pour les gargouilles
	const float bossAnimSpeed = 0.2f;  // 5 FPS pour les boss
	const float dirigeableAnimSpeed = 0.12f;  // 8.33 FPS pour les dirigeables

	// Suivi des temps accumulés pour chaque animation
	static float playerTimeAccumulator = 0.f;
	static float gargouilleTimeAccumulator = 0.f;
	static float bossTimeAccumulator = 0.f;
	static float dirigeableTimeAccumulator = 0.f;

	// Mise à jour du temps accumulé
	playerTimeAccumulator += elapsedTime;
	gargouilleTimeAccumulator += elapsedTime;
	bossTimeAccumulator += elapsedTime;
	dirigeableTimeAccumulator += elapsedTime;

	// Mise à jour de l'animation du joueur
	if (playerTimeAccumulator >= playerAnimSpeed) {
		animP.x++;
		if (animP.x * 54 >= this->player->getTexture().getSize().x) {
			animP.x = 0;  // Réinitialisation de l'animation
			animP.y++;    // Passer à la ligne suivante si nécessaire
			if (animP.y * 54 >= this->player->getTexture().getSize().y) {
				animP.y = 0;  // Réinitialiser si on dépasse les lignes
			}
		}
		this->player->getSprite().setTextureRect(sf::IntRect(animP.x * 54, animP.y * 54, 54, 54));
		playerTimeAccumulator = 0.f; // Réinitialiser l'accumulateur
	}

	// Mise à jour de l'animation des gargouilles
	if (gargouilleTimeAccumulator >= gargouilleAnimSpeed) {
		animG.x++;
		if (animG.x * 100 >= enemyTextures["Gargouille"]->getSize().x) {
			animG.x = 0;  // Réinitialisation de l'animation
			animG.y++;
			if (animG.y * 100 >= enemyTextures["Gargouille"]->getSize().y) {
				animG.y = 0;  // Réinitialiser si on dépasse les lignes
			}
		}
		gargouilleTimeAccumulator = 0.f; // Réinitialiser l'accumulateur
	}

	// Mise à jour de l'animation des boss
	if (bossTimeAccumulator >= bossAnimSpeed) {
		animB.x++;
		if (animB.x * 274 >= enemyTextures["Boss_1"]->getSize().x) {
			animB.x = 0;
			animB.y++;
			if (animB.y * 274 >= enemyTextures["Boss_1"]->getSize().y) {
				animB.y = 0;
			}
		}
		bossTimeAccumulator = 0.f; // Réinitialiser l'accumulateur
	}

	// Mise à jour de l'animation des dirigeables
	if (dirigeableTimeAccumulator >= dirigeableAnimSpeed) {
		animD.x++;
		if (animD.x * 47 >= enemyTextures["Dirigeable Ennemi"]->getSize().x) {
			animD.x = 0;
			animD.y++;
			if (animD.y * 47 >= enemyTextures["Dirigeable Ennemi"]->getSize().y) {
				animD.y = 0;
			}
		}
		dirigeableTimeAccumulator = 0.f; // Réinitialiser l'accumulateur
	}

	// Application des animations sur les sprites
	for (auto enemies = this->allEnemies.begin(); enemies != this->allEnemies.end(); ++enemies) {
		if (dynamic_cast<BigEnemy*>(*enemies) != nullptr) {
			(*enemies)->getSprite().setTextureRect(sf::IntRect(animD.x * 47, animD.y * 31, 47, 31));
		}
		if (dynamic_cast<CloseRangeEnemy*>(*enemies) != nullptr) {
			(*enemies)->getSprite().setTextureRect(sf::IntRect(animG.x * 100, animG.y * 100, 100, 100));
		}
		// Ajouter d'autres animations pour les autres types d'ennemis si nécessaire
	}
}


/*void updateAnim(sf::Sprite& sprite, sf::Vector2f& animFrame, const sf::Texture& texture, int frameWidth, int frameHeight, float animSpeed, sf::Clock& clock) {*
	if (clock.getElapsedTime().asSeconds() > animSpeed) {
		animFrame.x++;
		if (animFrame.x * frameWidth >= texture.getSize().x) {
			animFrame.x = 0; // Réinitialise à la première frame
		}
		sprite.setTextureRect(sf::IntRect(animFrame.x * frameWidth, animFrame.y * frameHeight, frameWidth, frameHeight));
		clock.restart();
	}
}*/



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
	if (this->player->getHp() <= 0) {

	}
}

void Game::update() {
	

	this->updateAnim();

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


