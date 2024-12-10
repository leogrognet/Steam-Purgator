#include "Enemy.h"

BigEnemy::BigEnemy()
{
}

BigEnemy::BigEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, float mult)
{

	this->attackCooldownMax = 0.5f;
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(size_x, size_y);
	this->speed = speed;


	this->startX = pos_x;  
	this->startY = pos_y;  
	this->amplitudeX = 100.f * mult; 
	this->amplitudeY = 50.f * mult;  
	this->frequencyX = 1.f/mult ;   
	this->frequencyY = 2.f/mult ;   

	this->moveClock.restart(); 
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

void BigEnemy::updateSelf(RenderWindow* window)
{
	float time = moveClock.getElapsedTime().asSeconds(); // Temps écoulé

	// Calcul du mouvement en "huit"
	float newX = this->startX + this->amplitudeX * sin(this->frequencyX * time); // Mouvement horizontal
	float newY = this->startY + this->amplitudeY * sin(this->frequencyY * time); // Mouvement vertical

	// Mise à jour de la position de l'ennemi
	this->sprite.setPosition(newX, newY);
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
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(size_x, size_y);
	this->speed = speed;

	this->startX = pos_x;           // Position de départ horizontale
	this->startY = pos_y;           // Position de départ verticale
	this->amplitudeY = 50.f;        // Amplitude verticale (distance de haut en bas)
	this->frequencyY = 1.f;         // Fréquence de l'oscillation verticale (la vitesse de l'oscillation)
	this->horizontalSpeed = speed;   // Vitesse de déplacement horizontal vers la droite (vous pouvez l'ajuster)
}

void RangedEnemy::updateSelf(RenderWindow* window)
{
	float time = moveClock.getElapsedTime().asSeconds(); // Temps écoulé depuis le dernier appel

	// Calcul du mouvement vertical basé sur un sinus
	float newY = this->startY + this->amplitudeY * sin(this->frequencyY * time);

	// Déplacement horizontal constant
	float newX = this->sprite.getPosition().x - horizontalSpeed;

	// Met à jour la position de l'ennemi
	this->sprite.setPosition(newX, newY);
}

void RangedEnemy::setSpeed(float speed)
{
}






//----------------------------------------------------------------------------------------------------------------------------------
//CloseRangeEnemy//-----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

CloseRangeEnemy::CloseRangeEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, Vector2f playerPos)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(size_x, size_y);
	this->speed = speed;

	// Calcul de la direction vers le joueur
	direction = playerPos - sprite.getPosition();  // Vecteur direction (du ennemi vers le joueur)
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= length;  // Normalisation pour une vitesse constante

	// Vous pouvez ajouter un facteur de vitesse ici si nécessaire
}

void CloseRangeEnemy::updateSelf(RenderWindow* window)
{
	// Déplacement vers la position du joueur
	Vector2f moveVector = direction * speed;  // Mouvement dans la direction calculée
	sprite.move(moveVector);  // Applique le mouvement
}





void CloseRangeEnemy::setSpeed(float speed)
{
	this->speed = speed;

	this->diagonalSpeedX = this->speed * cos(45.f * M_PI / 180.f);
	this->diagonalSpeedY = this->speed * sin(45.f * M_PI / 180.f);

}

