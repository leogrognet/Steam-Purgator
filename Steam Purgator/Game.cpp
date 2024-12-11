#include "Game.h"


Game::Game()
{
	this->window = new RenderWindow(VideoMode(1920, 1080), "Steam Purgator");
	this->window->setFramerateLimit(60);

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
	
	this->enemyTexture = new Texture;
	if (!this->enemyTexture->loadFromFile("asset/Avion.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}
}

int count;
void Game::spawnEnemy()
{
	deltaTimeElasped = deltaClock.getElapsedTime();

	if (deltaTimeElasped.asSeconds() >= 3.0f) {
		deltaClock.restart();
		int enemyX = window->getSize().x - 300;
		int enemyY = rand() % window->getSize().y;

		// Crée un RangedEnemy en passant la position du joueur
		Vector2f playerPos = this->player->getPos();  // Obtenez la position actuelle du joueur
		//this->allEnemies.push_back(new CloseRangeEnemy(enemyTexture, 2.0f, 2.0f, enemyX, enemyY, false, 0.01f, playerPos));  // Passez la position du joueur à l'ennemi
		this->allEnemies.push_back(new RangedEnemy(enemyTexture, 1.5f, 1.5f, enemyX, enemyY, false, 10.f));
		count++;
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



void Game::updateEnemy()
{

	for (auto enemies = this->allEnemies.begin(); enemies != this->allEnemies.end();) {
		(*enemies)->updateSelf(window);
		if ((*enemies)->canAttack() &&  dynamic_cast<RangedEnemy*> (*enemies) == nullptr) {
			this->allEnemyProjectiles.push_back(new Projectile(playerProjectileTexture,
				20.0f,
				20.0f,
				(*enemies)->getBounds().left + (*enemies)->getBounds().width,
				(*enemies)->getBounds().top + ((*enemies)->getBounds().height / 2),
				false,
				( (*enemies)->getSpeed() - 0.05f)
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

void Game::update()
{
	this->updatePlayer();

	this->spawnEnemy();

	this->updateInput();
	
	

	this->updateProjectile();

	this->updateEnemy();

	this->updatePlayer();

	

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


