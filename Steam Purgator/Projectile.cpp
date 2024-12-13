#include "Projectile.h"

Projectile::Projectile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(size_x, size_y);
	this->speed = speed;
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

Sprite Projectile::getSprite()
{
    return this->sprite;
}




void Projectile::updateSelf()
{
	this->sprite.move(this->speed , 0);
}

void Projectile::renderProjectile(RenderWindow* target)
{
	target->draw(this->sprite);
}



//-------------------------------------------------------------------------------------
//Class Missile------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
Missile::Missile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, vector<Sprite*>& enemiesSprites)
{
}

Missile::~Missile()
{
}

void Missile::updateSelf()
{
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;  // Normalisation
    }

    // Déplacer le missile dans la direction normalisée avec la vitesse
    this->sprite.move(direction * this->speed);
}




//-------------------------------------------------------------------------------------
//Class Laser------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

Laser::Laser(Texture* texture, float size_x, float size_y, float pos_x, float pos_y)
{
}

void Laser::updateSelf()
{
    if (active) {
        // Calculer la direction du laser à partir de la position du joueur
        Vector2f laserPos = this->getPos();
        Vector2f targetPos = this->targetDirection;  // Direction dans laquelle le laser se propage (par exemple, droite)

        // Calculer le vecteur direction du laser
        Vector2f direction = targetPos - laserPos;

        // Normaliser la direction pour obtenir une direction unitaire
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction /= length;  // Normalisation
        }

        // Calculer la longueur du rayon de laser (ici, on peut le limiter à la taille de la fenêtre par exemple)
        float maxDistance = 1000.0f;  // Peut être ajusté pour être la distance maximale du laser

        // Vérifier la collision avec les objets génériques (ennemis, objets, etc.)
        for (auto* objectSprite : allObjectsSprites) {
            if (objectSprite->getGlobalBounds().intersects(this->sprite.getGlobalBounds())) {
                // Si le laser touche un objet, arrêter à la position juste avant l'objet
                active = false;  // Vous pouvez ajuster ce comportement pour l'arrêter juste avant l'objet
                break;
            }
        }

        // Vérifier si le laser touche un bord de la fenêtre
        if (this->sprite.getPosition().x < 0 || this->sprite.getPosition().x > windowWidth ||
            this->sprite.getPosition().y < 0 || this->sprite.getPosition().y > windowHeight) {
            active = false;  // Désactiver le laser une fois qu'il atteint le bord de la fenêtre
        }
    }
}



Laser::~Laser()
{
}


//-------------------------------------------------------------------------------------
//Class Shield------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
Shield::Shield(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed)
{
}

void Shield::updateSelf()
{
}

Shield::~Shield()
{
}


//-------------------------------------------------------------------------------------
//Class Bomb------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
Bomb::Bomb(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed)
{
}

void Bomb::updateSelf()
{

}

Bomb::~Bomb()
{
}
