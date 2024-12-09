#include "Enemy.h"

BigEnemy::BigEnemy()
{
}

BigEnemy::BigEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed)
{
	this->attackCooldownMax = 0.5f;
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->speed = speed;
}

BigEnemy::~BigEnemy()
{

}


const Vector2f& BigEnemy::getPos() const
{
	return this->sprite.getPosition();
}

const FloatRect BigEnemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}


const bool BigEnemy::canAttack()
{
	shootTime = shootClock.getElapsedTime();
	if (this->shootTime.asSeconds() >= this->attackCooldownMax)
	{
		this->shootClock.restart();
		return true;
	}

	return false;
}

void BigEnemy::updateSelf()
{
	this->sprite.move(this->speed, 0);
}

void BigEnemy::renderEnemy(RenderWindow* target)
{
	target->draw(this->sprite);
}

Sprite BigEnemy::getSprite()
{
	return sprite;
}

float BigEnemy::getSpeed()
{
	return speed;
}

void BigEnemy::setHealth(int hp)
{
	this->health = hp;
}

void BigEnemy::setSpeed(float speed)
{
	this->speed = speed;
}

void BigEnemy::setDamage(int dmg)
{
	this->damage = dmg;
}


//----------------------------------------------------------------------------------------------------------------------------------
//Ennemi à distance//---------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

RangedEnemy::RangedEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed)
{
}



void RangedEnemy::updateSelf()
{
}

void RangedEnemy::setSpeed(float speed)
{
	this->speed = speed;
}




//----------------------------------------------------------------------------------------------------------------------------------
//CloseRangeEnemy//-----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

CloseRangeEnemy::CloseRangeEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed)
{
}

void CloseRangeEnemy::updateSelf()
{
}

void CloseRangeEnemy::setSpeed(float speed)
{
}

