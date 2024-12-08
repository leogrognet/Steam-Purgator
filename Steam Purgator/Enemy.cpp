#include "Enemy.h"

Enemy::Enemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->speed = 0.05f;
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


void Enemy::updateSelf()
{
	this->sprite.move(this->speed, 0);
}

void Enemy::renderEnemy(RenderWindow* target)
{
	target->draw(this->sprite);
}
