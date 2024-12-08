#include "Game.h"


Game::Game()
{
	this->initPlayer();
	this->initProjectile();
}

Game::~Game()
{
}

void Game::initPlayer()
{
	this->player = make_unique<Player>(100,100,1.0f,1.0f,500,500,false,0.01f, "asset/Perso stu.png");
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

void Game::updatePlayer(RenderWindow& window)
{
	
}

void Game::updateInput()
{
	this->player->movement();

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

}

void Game::updateProjectile(RenderWindow* window)
{
	for (auto it = this->allProjectiles.begin(); it != this->allProjectiles.end();) {
		(*it)->updateSelf();

		if ((*it)->getBounds().top + (*it)->getBounds().height < 0.f) {
			delete* it; // Libérer la mémoire
			it = this->allProjectiles.erase(it); // Supprimer de la liste
		}
		else {
			++it; // Passer au suivant
		}
	}
}

void Game::updateCollision(RenderWindow* window)
{
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= window->getSize().x)
	{
		this->player->setPosition(window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, window->getSize().y - this->player->getBounds().height);
	}
}

void Game::update(RenderWindow* window)
{

	this->player->update();

	this->updateInput();
	
	this->updateCollision(window);

	this->updateProjectile(window);

	this->updatePlayer(*window);



}

void Game::render(RenderWindow* window)
{
	window->clear(Color::White);


	this->player->render(*window);

	
	for (auto* it : this->allProjectiles) 
	{
		it->renderProjectile(window);
	}

	
	window->display();
}


