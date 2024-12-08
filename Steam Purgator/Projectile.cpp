#include "Projectile.h"

Projectile::Projectile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->speed = 0.01f;
}

Projectile::~Projectile()
{

}


const Vector2f& Projectile::getPos() const
{
	return this->sprite.getPosition();
}

const FloatRect Projectile::getBounds() const
{
	return this->sprite.getGlobalBounds();
}




void Projectile::updateSelf()
{
	this->sprite.move(this->speed , 0);
}

void Projectile::renderProjectile(RenderWindow* target)
{
	target->draw(this->sprite);
}




