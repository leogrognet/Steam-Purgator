#include "Projectile.h"

Projectile::Projectile(float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, Texture& texture) : speed(speed)
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(pos_x, pos_x);
	this->speed = speed;
}

Projectile::~Projectile()
{

}

void Projectile::updateSelf()
{
	this->sprite.move(this->speed , 0);
}

void Projectile::renderProjectile(RenderTarget* target)
{
	target->draw(this->sprite);
}






