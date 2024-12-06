#include "Player.h"

Player::Player(int hp, int maxHp, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed) : health(hp), maxHealth(maxHp), size_x(size_x), size_y(size_y), alive(alive), speed(speed), pos_x(pos_x), pos_y(pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::initVariables()
{
	this->speed = 2.f;


	this->maxHealth = 100;
	this->health = this->maxHealth;
}

void Player::initTexture()
{
	if (!this->texture.loadFromFile(""))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Player::initSprite()
{
	this->playerSprite.setTexture(this->texture);

	this->playerSprite.scale(0.1f, 0.1f);
}




const int& Player::getHp() const
{
	return this->health;
}

const int& Player::getHpMax() const
{
	return this->maxHealth;
}


void Player::setPosition(const Vector2f pos)
{
	this->playerSprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->playerSprite.setPosition(x, y);
}


const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}


void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}




void Player::movement()
{
	if (Keyboard::isKeyPressed(DirectionBind[Direction::Up])) { this->playerSprite.move(0, -speed); }
	if (Keyboard::isKeyPressed(DirectionBind[Direction::Down])) { this->playerSprite.move(0, speed); }
	if (Keyboard::isKeyPressed(DirectionBind[Direction::Left])) { this->playerSprite.move(-speed,0); }
	if (Keyboard::isKeyPressed(DirectionBind[Direction::Right])) { this->playerSprite.move(speed, 0); }
}

int Player::attack()
{
	if ((Keyboard::isKeyPressed(AttackBind[Attacks::LeftAttack]))) { return 1; }
	else { return 0; }
	if ((Keyboard::isKeyPressed(AttackBind[Attacks::RightAttack]))) { return 2; }
	else { return 0; }
	if ((Keyboard::isKeyPressed(AttackBind[Attacks::ChangeAttack]))) { return 3; }
	else { return 0; }
}








