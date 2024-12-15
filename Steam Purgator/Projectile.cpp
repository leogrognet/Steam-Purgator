#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::Projectile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, float speed) : markedForRemoval(false)
{
   
    this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(size_x, size_y);
	this->speed = speed;
    this->texture = texture;
    
    
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


void Projectile::updateSelf(Sprite sprite)
{
	this->sprite.move(this->speed , 0);
}

void Projectile::renderProjectile(RenderWindow* target)
{
	target->draw(this->sprite);
}

void Projectile::markForRemoval()
{
    this->markedForRemoval = true;
}

bool Projectile::isMarkedForRemoval() const
{
    return this->markedForRemoval;
}

void Projectile::updateAnim()
{
    AnimTime = AnimClock.getElapsedTime();
    if (AnimTime.asMilliseconds() > 100) {
        deltaTexture.x++;
        AnimClock.restart();
    }

    if (this->texture != nullptr && this->deltaTexture.x * this->width >= this->texture->getSize().x) {
        deltaTexture.x = 0;
    }
    this->sprite.setTextureRect(IntRect(deltaTexture.x * this->width, deltaTexture.y * this->height, this->width, this->height));
}



//-------------------------------------------------------------------------------------
//Class Missile------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
Missile::Missile(Texture* texture, float size_x, float size_y, float pos_x, float pos_y,float speed, int left, int top, int width, int height) 
{
    this->sprite.setTexture(*texture);
    this->sprite.setPosition(pos_x, pos_y);
    this->sprite.setScale(size_x, size_y);
    this->speed = speed;
    this->texture = texture;

    this->sprite.setTextureRect(IntRect(left, top, width, height));
    this->deltaTexture = Vector2f(1, 0);

    this->top = top;
    this->left = left;
    this->width = width;
    this->height = height;
}



void Missile::updateSelf(Sprite enemySprite)
{
    // Calculer la direction vers l'ennemi
    Vector2f enemyPos = enemySprite.getPosition();
    Vector2f missilePos = this->sprite.getPosition();

    // Calculer le vecteur direction du missile vers l'ennemi
    Vector2f direction = enemyPos - missilePos; // direction = (x_enemy - x_missile, y_enemy - y_missile)

    // Normaliser la direction pour obtenir une magnitude de 1
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length; // Normalisation
    }

    // Déplacer le missile dans la direction de l'ennemi avec la vitesse
    this->sprite.move(direction * this->speed);

    // Calculer l'angle du vecteur direction pour faire pivoter le missile
    float angle = atan2(-direction.y, -direction.x) * 180.f / 3.14159f; // Convertir en degrés

    // Appliquer la rotation au sprite pour qu'il pointe dans la direction du mouvement
    sprite.setRotation(angle);

    // Mettre à jour l'animation du missile
    this->updateAnim();
}







//-------------------------------------------------------------------------------------
//Class Laser------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

Laser::Laser(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, int left, int top, int width, int height)
{
}
void Laser::updateSelf(Sprite sprite)
{
}
/*
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
}*/





//-------------------------------------------------------------------------------------
//Class Shield------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
Shield::Shield(Texture* texture, float size_x, float size_y, float pos_x, float pos_y,int left, int top, int width, int height)
{
}

void Shield::updateSelf(Sprite sprite)
{
}




//-------------------------------------------------------------------------------------
//Class Bomb------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
Bomb::Bomb(Texture* texture, float size_x, float size_y, float pos_x, float pos_y,float speed, int left, int top, int width, int height)
{
}

void Bomb::updateSelf(Sprite sprite)
{

}
