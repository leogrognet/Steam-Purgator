#include "Player.h"

Player::Player(Texture* texture, Texture* healthTexture,  Texture* textureMissile, Texture* textureLaser, Texture* textureBouclier, Texture* textureBombe, int hp, int maxHp, float size_x, float size_y, float pos_x, float pos_y, float speed, int left, int top, int width, int height) : health(hp), maxHealth(maxHp)
{
	this->DirectionBind[Direction::Up] = Keyboard::Z;
	this->DirectionBind[Direction::Down] = Keyboard::S;
	this->DirectionBind[Direction::Left] = Keyboard::Q;
	this->DirectionBind[Direction::Right] = Keyboard::D;

	this->AttackBind[Attacks::LeftAttack] = Keyboard::Space;
	this->AttackBind[Attacks::RightAttack] = Keyboard::W;
	this->AttackBind[Attacks::ChangeAttack] = Keyboard::LAlt;

	this->texture = texture;
	this->healthTexture = healthTexture;

	this->textureMissile = textureMissile;
	this->textureLaser = textureLaser;
	this->textureBouclier = textureBouclier;
	this->textureBombe = textureBombe;
	if (textureMissile == nullptr) {
		cout << NULL << endl;
	}

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
	this->initSprite();
	this->playerSprite.setTextureRect(IntRect(this->width,this->height, this->width, this->height));
}

Player::~Player()
{
}

void Player::initVariables()
{

	this->attackCooldownMax = 0.5f;
	this->maxHealth = 100;
	this->health = 100;
	
	this->MissileMax = 50;
	this->LaserMax = 100;
	this->BombMax = 5;
	this->ShieldMax = 100;
}



void Player::initSprite()
{
	this->playerSprite.setTexture(*texture);
	this->playerSprite.setPosition(0, 500);
	this->playerSprite.scale(this->size_x, this->size_y);

	this->healthSprite.setTexture(*healthTexture);
	this->healthSprite.scale(this->size_x +1, this->size_y );
	this->healthSprite.setPosition(10, 0);

	this->healthBar.setFillColor(Color::Green);
	this->healthBar.setPosition(this->healthSprite.getPosition().x + 50, this->healthSprite.getPosition().y + (this->healthSprite.getGlobalBounds().height /3) + 5);
	this->healthBar.setSize(Vector2f(this->healthSprite.getGlobalBounds().width - 75, 10));



	this->NbMissile.setTexture(*textureMissile);
	this->NbMissile.scale(0.8, 0.8);
	this->NbMissile.setPosition(this->healthSprite.getPosition().x + this->healthSprite.getGlobalBounds().width + 50, 30);

	this->NbLaser.setTexture(*textureLaser);
	this->NbLaser.scale(2, 2);
	this->NbLaser.setPosition(this->NbMissile.getPosition().x + this->NbMissile.getGlobalBounds().width + 50, 20);

	this->NbBouclier.setTexture(*textureBouclier);
	this->NbBouclier.scale(0.8, 0.8);
	this->NbBouclier.setPosition(this->NbLaser.getPosition().x + this->NbLaser.getGlobalBounds().width + 50, 20);

	this->NbBombe.setTexture(*textureBombe);
	this->NbBombe.scale(1, 1);
	this->NbBombe.setPosition(10, 0);
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
	return *texture;
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

	if (this->deltaTexture.x * this->width >= texture->getSize().x) {
		deltaTexture.x = 0;
	}

	float percent = (static_cast<float>(this->health) / static_cast<float>(this->maxHealth));

	this->playerSprite.setTextureRect(IntRect(deltaTexture.x * this->width, deltaTexture.y * this->height, this->width, this->height));
	this->healthBar.setSize(Vector2f((this->healthSprite.getGlobalBounds().width - 75) * percent, 10));
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
	target.draw(this->healthBar);
	target.draw(this->playerSprite);
	target.draw(this->healthSprite);
	target.draw(this->NbMissile);
	target.draw(this->NbLaser);
	target.draw(this->NbBouclier);
	
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








