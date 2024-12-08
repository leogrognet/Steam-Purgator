#include "Game.h"


Game::Game()
{
	this->initPlayer();
	this->initProjectile();
	this->initEnemy();
}

Game::~Game()
{
}

void Game::initPlayer()
{
	this->player = make_unique<Player>(100,100,1.0f,1.0f,500,500,false,0.03f, "asset/Perso stu.png");
}

void Game::initProjectile()
{
	this->texture = new Texture;
	string imagePath = "asset/boulet de canon.png";
	cout << "test";
	if (!this->texture->loadFromFile("asset/boulet de canon.png"))
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
	this->allEnemies.push_back( new Enemy(enemyTexture,
		20.0f,
		20.0f,
		300,
		300,
		false,
		0.0f));
}



bool Game::run(RenderWindow *window)
{	
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
		this->allProjectiles.push_back(new Projectile(texture,
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
		for (auto projectiles = this->allProjectiles.begin(); projectiles != this->allProjectiles.end();) {

			if ((*projectiles)->getBounds().intersects((*enemies)->getBounds())) {
				delete* enemies;
				enemies = this->allEnemies.erase(enemies); 

				delete* projectiles;
				projectiles = this->allProjectiles.erase(projectiles); 
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
	for (auto it = this->allProjectiles.begin(); it != this->allProjectiles.end();) {
		(*it)->updateSelf();

		if ((*it)->getBounds().top + (*it)->getBounds().height < 0.f) {
			delete* it; 
			it = this->allProjectiles.erase(it); 
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

	

	this->updateInput(window);
	
	

	this->updateProjectile(window);

	this->updateEnemy();

	this->updatePlayer(window);



}

void Game::render(RenderWindow* window)
{
	window->clear(Color::White);


	this->player->render(*window);

	
	for (auto* it : this->allProjectiles) 
	{
		it->renderProjectile(window);
	}

	for (auto* it : this->allEnemies)
	{
		it->renderEnemy(window);
	}
	
	window->display();
}


