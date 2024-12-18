#include "Ammo.h"

Ammunition::Ammunition(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, float speed, int Ammo)
{
    this->sprite.setTexture(*texture);
    this->sprite.setPosition(pos_x, pos_y);
    this->sprite.setScale(size_x, size_y);
    this->speed = speed;
    this->texture = texture;
    this->Ammo = Ammo;
    Ammochoice();
    
}

Ammunition::~Ammunition()
{
}

void Ammunition::updateSelf()
{
    this->sprite.move(0, this->speed);
}

void Ammunition::markForRemoval()
{
    this->markedForRemoval = true;
}

bool Ammunition::isMarkedForRemoval() const
{
    return this->markedForRemoval;
}

void Ammunition::Ammochoice()
{
    switch(Ammo) {
    case 1:
        this->AmmoMax = 10;
    case 2:
        this->AmmoMax = 15;
    case 3:
        this->AmmoMax = 20;
    case 4:
        this->AmmoMax = 25;
    }
    
}

int Ammunition::getAmmo()
{
    return this->Ammo;
}

void Ammunition::setAmmoMax(int AmmoMax)
{
    this->AmmoMax = AmmoMax;
}

int Ammunition::getAmmoMax()
{
    return this->AmmoMax;
}

void Ammunition::renderAmmo(RenderWindow* target)
{
    target->draw(this->sprite);
}
