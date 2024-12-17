#include <SFML/Graphics.hpp>


using namespace sf;

#pragma once

class setBG {
public:
	setBG(Texture* frontTexture, Texture* backTexture, float sizeX, float sizeY, float posX, float posY);
	Sprite frontSprite;
	Sprite backSprite;
	void renderBg(RenderWindow* target);
	void animBG(RenderWindow* target);

};

