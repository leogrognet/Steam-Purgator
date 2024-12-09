#include "Player.h"

Player::Player(int hp, int maxHp, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, string image) : health(hp), maxHealth(maxHp)
{
	this->DirectionBind[Direction::Up] = Keyboard::Z;
	this->DirectionBind[Direction::Down] = Keyboard::S;
	this->DirectionBind[Direction::Left] = Keyboard::Q;
	this->DirectionBind[Direction::Right] = Keyboard::D;

	this->AttackBind[Attacks::LeftAttack] = Keyboard::Space;

	this->speed = speed;

	this->initVariables();
	this->initTexture(image);
	this->initSprite();
}

Player::~Player()
{
}

void Player::initVariables()
{


	this->attackCooldownMax = 0.5f;

	this->maxHealth = 100;
	this->health = this->maxHealth;
}

void Player::initTexture(string image)
{
	if (!this->texture.loadFromFile(image))
	{
		cerr << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << endl;
	}
}

void Player::initSprite()
{
	this->playerSprite.setTexture(this->texture);

	this->playerSprite.scale(1.0f, 1.0f);
}




const int& Player::getHp() const
{
	return this->health;
}

const int& Player::getHpMax() const
{
	return this->maxHealth;
}

const Vector2f& Player::getPos() const
{
	return this->playerSprite.getPosition();
}

const FloatRect Player::getBounds() const
{
	return this->playerSprite.getGlobalBounds();
}

void Player::setHp(const int hp)
{
	this->health = hp;
}

void Player::loseHp(const int value)
{
	this->health -= value;
	if (this->health < 0)
		this->health = 0;
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
	shootTime = shootClock.getElapsedTime();
	if (this->shootTime.asSeconds() >= this->attackCooldownMax)
	{
		this->shootClock.restart();
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	this->shootTime = this->shootClock.getElapsedTime();
	if (this->shootTime.asSeconds() > this->attackCooldownMax) {
		shootClock.restart();
	}
}


void Player::update(RenderWindow* window)
{

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->playerSprite);
}




void Player::movement(RenderWindow* window)
{
	if (Keyboard::isKeyPressed(DirectionBind[Direction::Up])) { if(this->playerSprite.getPosition().y > 0) 
		this->playerSprite.move(0, -speed); }
	else if (Keyboard::isKeyPressed(DirectionBind[Direction::Down])) { 
		if (this->playerSprite.getPosition().y < (window->getSize().y - playerSprite.getGlobalBounds().height)) {
			this->playerSprite.move(0, speed);
			cout << this->playerSprite.getPosition().y << endl;
		}
		}
	if (Keyboard::isKeyPressed(DirectionBind[Direction::Left])) { if (this->playerSprite.getPosition().x > 0) 
		this->playerSprite.move(-speed,0); }
	else if (Keyboard::isKeyPressed(DirectionBind[Direction::Right])) { if (this->playerSprite.getPosition().x < (window->getSize().x))
		this->playerSprite.move(speed, 0); }
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








