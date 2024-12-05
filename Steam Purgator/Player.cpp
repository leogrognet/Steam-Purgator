#include "Player.h"

Player::Player(Texture Texture, int hp, int maxHp, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed) : health(hp), maxHealth(maxHp), size_x(size_x), size_y(size_y), alive(alive), speed(speed), pos_x(pos_x), pos_y(pos_y)
{
}

Player::~Player()
{
}

void Player::movement()
{
	if (Keyboard::isKeyPressed(DirectionBind[Direction::Up])) { playerSprite.move(0, -speed); }
	if (Keyboard::isKeyPressed(DirectionBind[Direction::Down])) { playerSprite.move(0, speed); }
	if (Keyboard::isKeyPressed(DirectionBind[Direction::Left])) { playerSprite.move(-speed,0); }
	if (Keyboard::isKeyPressed(DirectionBind[Direction::Right])) { playerSprite.move(speed, 0); }
}

void Player::attack()
{
	if ((Keyboard::isKeyPressed(AttackBind[Attacks::LeftAttack]))) {  };
	if ((Keyboard::isKeyPressed(AttackBind[Attacks::RightAttack]))) {};
	if ((Keyboard::isKeyPressed(AttackBind[Attacks::ChangeAttack]))) {};

}

void Player::destroyPlayer()
{
	
}

void Player::initBullets()
{

}






