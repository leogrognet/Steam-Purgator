#include "Enemy.h"

BigEnemy::BigEnemy()
{
}

BigEnemy::BigEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, float mult, int left, int top, int width, int height)
{


	this->move_count = false;
	this->attackCooldownMax = 0.5f;

	
	this->texture = texture;
	this->sprite.setTexture(*texture);
	this->sprite.setTextureRect(IntRect(left,top,width,height));
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(size_x, size_y);

	this->deltaTexture = Vector2f(1, 0);

	this->top = top;
	this->left = left;
	this->width = width;
	this->height = height;


	this->speed = speed;
	this->health = 100;
	this->damage = 10;


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

int BigEnemy::getHealth()
{
	return this->health;
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

	
	
	float time = moveClock.getElapsedTime().asSeconds(); 

	if (this->sprite.getPosition().x > (window->getSize().x - 300) && move_count == false) {
		this->sprite.move(-speed, 0);
	}
	if (this->sprite.getPosition().x <= (window->getSize().x -300) && this->move_count == false) {
		this->startX = this->sprite.getPosition().x;
		this->startY = this->sprite.getPosition().y;
		this->move_count = true;
	}
	else if (this->move_count == true ) {
		float newX = this->startX + this->amplitudeX * sin(this->frequencyX * time); 
		float newY = this->startY + this->amplitudeY * sin(this->frequencyY * time); 
		this->sprite.setPosition(newX, newY);
	}

	updateAnim();
}

void BigEnemy::renderEnemy(RenderWindow* target)
{
	target->draw(this->sprite);
}

void BigEnemy::updateAnim()
{
	AnimTime = AnimClock.getElapsedTime();
	if (AnimTime.asMilliseconds() > 100){
		deltaTexture.x++;
		AnimClock.restart();
	}

	if (this->texture != nullptr && this->deltaTexture.x * this->width >= this->texture->getSize().x) {
		deltaTexture.x = 0;
	}
	this->sprite.setTextureRect(IntRect(deltaTexture.x * this->width, deltaTexture.y * this->height, this->width, this->height));
}

Sprite BigEnemy::getSprite()
{
	return  this->sprite;
}

float BigEnemy::getSpeed()
{
	return this->speed;
}

int BigEnemy::getDamage()
{
	return this->damage;
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

void BigEnemy::markForRemoval()
{
	this->markedForRemoval = true;
}

bool BigEnemy::isMarkedForRemoval() const
{
	return this->markedForRemoval;
}


//----------------------------------------------------------------------------------------------------------------------------------
//Ennemi à distance//---------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

RangedEnemy::RangedEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed)
{
	this->texture = texture;
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(size_x, size_y);

	this->deltaTexture = Vector2f(1, 0);

	this->damage = 10;
	this->speed = speed;
	this->health = 20;

	this->attackCooldownMax = 0.5f;
	this->startX = pos_x;           // Position de départ horizontale
	this->startY = pos_y;           // Position de départ verticale
	this->amplitudeY = 50.f;        // Amplitude verticale (distance de haut en bas)
	this->frequencyY = 1.f;         // Fréquence de l'oscillation verticale (la vitesse de l'oscillation)
	this->horizontalSpeed = speed;   // Vitesse de déplacement horizontal vers la droite (vous pouvez l'ajuster)
}

void RangedEnemy::updateSelf(RenderWindow* window)
{
	float time = moveClock.getElapsedTime().asSeconds(); // Temps écoulé depuis le dernier appel


	float newY = this->startY + this->amplitudeY * sin(this->frequencyY * time);


	float newX = this->sprite.getPosition().x - horizontalSpeed;


	this->sprite.setPosition(newX, newY);
}

void RangedEnemy::setSpeed(float speed)
{
}






//----------------------------------------------------------------------------------------------------------------------------------
//CloseRangeEnemy//-----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

CloseRangeEnemy::CloseRangeEnemy(Texture* texture, float size_x, float size_y, float pos_x, float pos_y, bool alive, float speed, Vector2f playerPos, int left, int top, int width, int height )
{

	this->texture = texture;
	if (this->texture == nullptr) {
		cout << "unull" << endl;
		this->sprite.setTexture(*texture);
	}
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.setScale(size_x, size_y);
	this->sprite.setTextureRect(IntRect(left, top, width, height));


	this->top = top;
	this->left = left;
	this->width = width;
	this->height = height;

	this->damage = 10;
	this->health = 20;
	this->speed = speed;

	deltaTexture = Vector2f(1, 0);

	
	direction = playerPos - sprite.getPosition();  
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= length;  


}

void CloseRangeEnemy::updateSelf(RenderWindow* window)
{
	this->updateAnim();
	Vector2f moveVector = direction * speed;  
	sprite.move(moveVector);  
}






void CloseRangeEnemy::setSpeed(float speed)
{
	this->speed = speed;

	this->diagonalSpeedX = this->speed * cos(45.f * M_PI / 180.f);
	this->diagonalSpeedY = this->speed * sin(45.f * M_PI / 180.f);

}

