#include "Player.h"

Player::Player(int hp, int maxHp, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, string image, int left, int top, int width, int height) : health(hp), maxHealth(maxHp)
{
	this->DirectionBind[Direction::Up] = Keyboard::Z;
	this->DirectionBind[Direction::Down] = Keyboard::S;
	this->DirectionBind[Direction::Left] = Keyboard::Q;
	this->DirectionBind[Direction::Right] = Keyboard::D;

	this->AttackBind[Attacks::LeftAttack] = Keyboard::Space;
	this->AttackBind[Attacks::RightAttack] = Keyboard::W;
	this->AttackBind[Attacks::ChangeAttack] = Keyboard::LAlt;


	this->speed = speed;
	this->damage = 10;

	this->deltaTexture = Vector2f(1, 0);
	this->size_x = size_x;
	this->size_y = size_y;
	this->top = top;
	this->left = left;
	this->width = width;
	this->height = height;

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
	this->MissileMax = 50;
	this->LaserMax = 100;
	this->BombMax = 5;
	this->ShieldMax = 100;
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

	this->playerSprite.scale(this->size_x, this->size_y);
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

const float Player::getSpeed() const
{
	return this->speed;
}

const int Player::getDamage() const
{
	return this->damage;
}

Sprite Player::getSprite()
{
	return this->playerSprite;
}

const Texture Player::getTexture() const
{
	return this->texture;
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



void Player::updateAnim()
{
	AnimTime = AnimClock.getElapsedTime();
	if (AnimTime.asMilliseconds() > 100) {
		deltaTexture.x++;
		AnimClock.restart();
	}

	if (this->deltaTexture.x * this->width >= this->texture.getSize().x) {
		deltaTexture.x = 0;
	}
	this->playerSprite.setTextureRect(IntRect(deltaTexture.x * this->width, deltaTexture.y * this->height, this->width, this->height));
}


void Player::update(RenderWindow* window)
{
	if (this->weaponCount["missileUse"] > this->MissileMax) {
		this->weaponCount["missileUse"] = this->MissileMax;
	}
	if (this->weaponCount["shieldUse"] > this->ShieldMax) {
		this->weaponCount["shieldUse"] = this->ShieldMax;
	}
	if (this->weaponCount["laserUse"] > this->LaserMax) {
		this->weaponCount["laserUse"] = this->LaserMax;
	}
	if (this->weaponCount["bombUse"] > this->BombMax) {
		this->weaponCount["bombUse"] = this->BombMax;
	}
	movement(window);
	attack();
	updateAnim();
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
	else if ((Keyboard::isKeyPressed(AttackBind[Attacks::RightAttack]))) {  return 2; }
	else if ((Keyboard::isKeyPressed(AttackBind[Attacks::ChangeAttack]))) { return 3; }
	else { return 0; }
}








