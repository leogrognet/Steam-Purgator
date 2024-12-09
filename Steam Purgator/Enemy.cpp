#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed)
{
	this->attackCooldownMax = 0.5f;
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->speed = speed;
}

Enemy::~Enemy()
{

}


const Vector2f& Enemy::getPos() const
{
	return this->sprite.getPosition();
}

const FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}


const bool Enemy::canAttack()
{
	shootTime = shootClock.getElapsedTime();
	if (this->shootTime.asSeconds() >= this->attackCooldownMax)
	{
		this->shootClock.restart();
		return true;
	}

	return false;
}

void Enemy::updateSelf()
{
	this->sprite.move(this->speed, 0);
}

void Enemy::renderEnemy(RenderWindow* target)
{
	target->draw(this->sprite);
}

Sprite Enemy::getSprite()
{
	return sprite;
}

float Enemy::getSpeed()
{
	return speed;
}

void Enemy::setSpeed(float speed)
{
	this->speed = speed;
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

const bool RangedEnemy::canAttack()
{
	return false;
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

const bool CloseRangeEnemy::canAttack()
{
	return false;
}
