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
    this->markedForRemoval = false;

    
    
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




void Projectile::updateSelf(Sprite enemySprite, Sprite playerSprite )
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

    this->max_ammo = 40;
    this->ammo = 0;
}



void Missile::updateSelf(Sprite enemySprite, Sprite playerSprite )
{
    // Calculer la direction vers l'ennemi si l'ennemi existe
    Vector2f direction;

    if (enemySprite.getTexture() !=nullptr) {
        // Si l'ennemi existe, calculer la direction vers lui
        Vector2f enemyPos = Vector2f(enemySprite.getPosition().x+(enemySprite.getGlobalBounds().width/2), enemySprite.getPosition().y + (enemySprite.getGlobalBounds().height / 2));
        Vector2f missilePos = this->sprite.getPosition();

        direction = enemyPos - missilePos; // direction = (x_enemy - x_missile, y_enemy - y_missile)

        // Normaliser la direction pour obtenir une magnitude de 1
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction /= length; // Normalisation
        }
    }
    else {
        // Si l'ennemi n'existe pas, le missile va tout droit
        direction = Vector2f(1.f, 0.f); // Direction initiale vers la droite (ou autre direction par défaut)
    }

    // Déplacer le missile dans la direction calculée (soit vers l'ennemi, soit tout droit)

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

Laser::Laser(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, Sprite player)
{

    this->active = false;
    this->sprite.setTexture(*texture);
    this->sprite.setPosition(pos_x, pos_y);
    this->sprite.setScale(size_x, size_y);
    this->texture = texture;
    this->max_ammo = 100;
    this->ammo = 0;
}


void Laser::updateSelf(Sprite enemySprite, Sprite playerSprite)
{

    Vector2f enemyPos = enemySprite.getPosition();
    Vector2f missilePos = this->sprite.getPosition();
    // Position initiale du laser
    this->sprite.setPosition(playerSprite.getPosition());

    // Direction du laser (par exemple, vers la droite ou une direction spécifiée)
    Vector2f laserDirection = Vector2f(1.f, 0.f); // Exemple : direction vers la droite
    float laserLength = 1000.f; // Longueur du laser (peut être ajustée)

    // Vérification de la collision avec un ennemi dans le chemin du laser
    if (checkLaserCollisionWithEnemy(playerSprite.getPosition(), laserDirection, laserLength, enemySprite)) {
        // Si une collision est détectée, ajuster la longueur du laser
        laserLength = calculateCollisionDistance(playerSprite.getPosition(), laserDirection, enemySprite);
    }

    // Mise à jour de la longueur du laser (ajuster le sprite en fonction de la distance)
    this->sprite.setScale(laserLength / sprite.getTexture()->getSize().x, 1.f);

    // Calculer l'angle du laser pour qu'il soit orienté correctement
    float angle = atan2(laserDirection.y, laserDirection.x) * 180.f / 3.14159f; // Convertir en degrés
    sprite.setRotation(angle);

    // Mettre à jour l'animation du laser si nécessaire
    this->updateAnim();
}



bool Laser::checkLaserCollisionWithEnemy(const Vector2f& laserStart, const Vector2f& laserDirection, float laserLength, const Sprite& enemySprite)
{
    // Calculer la direction du laser
    Vector2f direction = laserDirection;
    float laserEndX = laserStart.x + laserDirection.x * laserLength;
    float laserEndY = laserStart.y + laserDirection.y * laserLength;
    FloatRect laserBounds(laserStart.x, laserStart.y, laserEndX - laserStart.x, laserEndY - laserStart.y);

    // Vérifie si le laser entre en collision avec l'ennemi
    return laserBounds.intersects(enemySprite.getGlobalBounds());
}

float Laser::calculateCollisionDistance(const Vector2f& laserStart, const Vector2f& laserDirection, const Sprite& enemySprite)
{
    // Calculer la position de l'ennemi
    Vector2f enemyPos = enemySprite.getPosition();

    // Calculer la distance entre la position du laser et la position de l'ennemi
    float distance = sqrt(pow(enemyPos.x - laserStart.x, 2) + pow(enemyPos.y - laserStart.y, 2));

    // Retourner la distance à laquelle le laser doit s'arrêter
    return distance;
}


void Laser::renderProjectile(RenderWindow* target)
{
    if (this->active) {
        target->draw(this->sprite);
    }
}

void Laser::setActive(bool setter)
{
    this->active = setter;
}


void Laser::followPlayer(Sprite player)
{
    this->sprite.setPosition(player.getPosition().x + player.getGlobalBounds().width, player.getPosition().y + player.getGlobalBounds().height/2);

}










//-------------------------------------------------------------------------------------
//Class Shield------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
Shield::Shield(Texture* texture, float size_x, float size_y, float pos_x, float pos_y)
{
    this->active = false;
    this->sprite.setTexture(*texture);
    this->sprite.setPosition(pos_x, pos_y);
    this->sprite.setScale(size_x, size_y);
    this->texture = texture;
    this->max_ammo = 100;
    this->ammo = 0;
}

void Shield::setActive(bool setter)
{
    this->active = setter;
}

void Shield::followPlayer(Sprite player)
{
    this->sprite.setPosition(player.getPosition().x + player.getGlobalBounds().width, player.getPosition().y + player.getGlobalBounds().height / 2);

}

void Shield::renderProjectile(RenderWindow* target)
{
    if (this->active) {
        target->draw(this->sprite);
    }
}

//-------------------------------------------------------------------------------------
//Class Bomb------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
Bomb::Bomb(Texture* texture, float size_x, float size_y, float pos_x, float pos_y,float speed, int left, int top, int width, int height)
{
}

