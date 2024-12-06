#include "Game.h"

Game::Game() : player(1, 1, 10, 10, 0, 0, true, 0.1f)
{
	
	player.DirectionBind[player.Direction::Up] = Keyboard::Z;
	player.DirectionBind[player.Direction::Down] = Keyboard::S;
	player.DirectionBind[player.Direction::Left] = Keyboard::Q;
	player.DirectionBind[player.Direction::Right] = Keyboard::D;
	player.AttackBind[player.Attacks::LeftAttack] = Keyboard::A; 
	loadTexture();
}

Game::~Game()
{
}



void Game::updatePlayer(Player& player, RenderWindow& window)
{

	player.movement();
	//window.draw(player.playerSprite);
	//test.sprite.setPosition(player.pos_x, player.pos_y);
	if (player.attack() == 1 && count < 100) { count++; Projectile proj(10, 10, player.pos_x, player.pos_y, true, 10, textureBlueBird); this->allProjectiles.push_back(proj); }
	
}

void Game::updateEnemy()
{
}

void Game::updateProjectile(RenderWindow& window)
{
	for (auto it : this->allProjectiles) {
		it.updateSelf();
		//window.draw(it.sprite);
	}
}

void Game::updateConfig()
{
}
