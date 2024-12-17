#include "setBackGround.h"

setBG::setBG(Texture* frontTexture, Texture* backTexture, float sizeX, float sizeY, float posX, float posY)
{

	this->frontSprite.setTexture(*frontTexture);
	this->frontSprite.setPosition(posX, posY);
	this->frontSprite.setScale(sizeX, sizeY);

	this->backSprite.setTexture(*backTexture);

}

void setBG::renderBg(RenderWindow* target)
{
	target->draw(this->frontSprite);
	target->draw(this->backSprite);
}

void setBG::animBG(RenderWindow* target)
{
	if (this->frontSprite.getPosition().x <= -347) {
		this->frontSprite.setPosition(Vector2f(target->getSize().x + 350, 384));
	}
	if (this->frontSprite.getPosition().x > -347 and this->frontSprite.getPosition().x <= target->getSize().x + 350) {
		this->frontSprite.setPosition(Vector2f(this->frontSprite.getPosition().x - 10, 384));
	}
}