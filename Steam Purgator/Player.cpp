#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::movement()
{
	if (Keyboard::isKeyPressed(Keybind[Direction::Up])) { playerSprite.move(0, -speed); }
	if (Keyboard::isKeyPressed(Keybind[Direction::Down])) { playerSprite.move(0, speed); }
	if (Keyboard::isKeyPressed(Keybind[Direction::Left])) { playerSprite.move(-speed,0); }
	if (Keyboard::isKeyPressed(Keybind[Direction::Right])) { playerSprite.move(speed, 0); }
}
