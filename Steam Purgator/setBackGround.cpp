#include "setBackGround.h"

setBG::setBG(Texture* frontTexture, Texture* backTexture,Texture* backtexture2, Texture* backtexture3,Texture* backtexture4,Texture* backtexture5 ,RenderWindow* target)
{

	this->frontSprite.setTexture(*frontTexture);
    this->frontSprite.setScale(0.8, 0.8);
	this->frontSprite.setPosition(500.f, 504);
	

    this->cloud1.setTexture(*backtexture2);
    this->cloud1.setPosition(50, 100);
    this->cloud1.setScale(1, 1);

    this->cloud2.setTexture(*backtexture3);
    this->cloud2.setPosition(800, 50);
    this->cloud2.setScale(5, 5);

    this->BG1.setTexture(*backtexture4);
    this->BG1.setPosition(0, 0);
    this->BG1.setScale(3+(1.f/3.f), 3.1);

    this->BG2.setTexture(*backtexture5);
    this->BG2.setPosition(target->getSize().x, 0);
    this->BG2.setScale(3 + (1.f / 3.f), 3.1);

    this->BG3.setTexture(*backtexture5);
    this->BG3.setPosition(target->getSize().x, 0);
    this->BG3.setScale(3.6, 3.1);

	this->backSprite.setTexture(*backTexture);
    this->backSprite.setPosition(0, target->getSize().y - 100);

}

void setBG::renderBg(RenderWindow* target)
{

    target->draw(this->BG1);
    target->draw(this->BG2);
    cout << this->BG1.getPosition().x + BG1.getGlobalBounds().width << endl;
   // target->draw(this->BG3);
    target->draw(this->backSprite);
    
    target->draw(this->cloud2);
    target->draw(this->cloud1);
    
	target->draw(this->frontSprite);
}

void setBG::animBG(RenderWindow* target, Sprite& sprite, int posY, float speed)
{
    // Si le sprite dépasse la gauche de la fenêtre, réinitialisez-le à droite
    if (speed < 0) {
        if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width < 0) {
            sprite.setPosition(Vector2f(target->getSize().x , posY));
        }
        else {
            // Déplacez le sprite uniquement s'il est visible ou en train de traverser l'écran
            sprite.move(speed, 0);
        }
    }
    else {
        if (sprite.getGlobalBounds().left > target->getSize().x ) {
            sprite.setPosition(- sprite.getGlobalBounds().width, posY);
        }
        else {
            // Déplacez le sprite uniquement s'il est visible ou en train de traverser l'écran
            sprite.move(speed, 0);
        }
    }

  
    // Debugging pour vérifier la position
    
}

void setBG::updateScrolling(RenderWindow* window) {
    animBG(window,this->frontSprite, 504,-5.0f);
    animBG(window, this->cloud1, 100, 3.0f);
    animBG(window, this->cloud2, 50, 1.0f);
    animBG(window, this->BG1, 0, -10.0f);
    animBG(window, this->BG2, 0, -10.0f);
   // this->BG2.setPosition(this->BG1.getPosition().x + this->BG1.getGlobalBounds().width,0);

}