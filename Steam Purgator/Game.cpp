#include "Game.h"


Game::Game(RenderWindow* window)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	this->initPlayer();
	this->initProjectile();
	this->initEnemy();
}

Game::~Game()
{
}

void Game::initPlayer()
{
	this->player = make_unique<Player>(100,100,1.0f,1.0f,500,500,false,0.1f, "asset/Perso stu.png");
}

void Game::initProjectile()
{
	this->playerProjectileTexture = new Texture;
	string imagePath = "asset/boulet de canon.png";
	cout << "test";
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
	if (!this->enemyTexture->loadFromFile("asset/Dirigeable ennemie.png"))
	{
		cerr << "ERROR::PROJECTILE::INITTEXTURE::Could not load texture file." << endl;
	}
}


void Game::spawnEnemy(RenderWindow* window)
{

	
	deltaTimeElasped = deltaClock.getElapsedTime();
	cout << deltaTimeElasped.asSeconds()<< endl;
	if (deltaTimeElasped.asSeconds() >= 3.0f) {
		deltaClock.restart();
		cout << "test2" << endl;
		int enemyX = window->getSize().x - 100;
		int enemyY = rand() % 600;
		this->allEnemies.push_back(new BigEnemy(enemyTexture, 20.0f, 20.0f, enemyX, enemyY, false, -0.05f));
	}
}

bool Game::run(RenderWindow *window)
{	
	startClock.restart();
	startTimeElapsed = startClock.getElapsedTime();
	this->game_on = true;
	while (game_on) {

	Event gameEvent;
	while (window->pollEvent(gameEvent))
	{
		if (gameEvent.Event::type == Event::Closed) {
			window->close();
		}
		if (gameEvent.Event::KeyPressed && gameEvent.Event::key.code == Keyboard::Escape) {
			this->game_on = false;
		}
	}
	
		this->render(window);
		this->update(window);
		
	}
	return this->game_on;
}



void Game::updateInput(RenderWindow* window)
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
			0.1f
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
		(*enemies)->updateSelf();
		if ((*enemies)->canAttack()) {
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

void Game::updateProjectile(RenderWindow* window)
{
	for (auto it = this->allPlayerProjectiles.begin(); it != this->allPlayerProjectiles.end();) {
		(*it)->updateSelf();

		if ((*it)->getBounds().left + (*it)->getBounds().width > 800) {
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

void Game::updatePlayer(RenderWindow* window)
{
	this->player->update(window);
}

void Game::update(RenderWindow* window)
{
	this->updatePlayer(window);

	this->spawnEnemy(window);

	this->updateInput(window);
	
	

	this->updateProjectile(window);

	this->updateEnemy();

	this->updatePlayer(window);

	

}

void Game::render(RenderWindow* window)
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


