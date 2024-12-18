#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

#ifndef SETBACKGROUND_H
#define SETBACKGROUND_H



class setBG {
public:
	setBG(Texture* frontTexture, Texture* backTexture, Texture* backtexture2, Texture* backtexture3, Texture* backtexture4, Texture* backtexture5, RenderWindow* target);
	Sprite frontSprite;
	Sprite backSprite;
	Sprite cloud1;
	Sprite cloud2;
	Sprite BG1, BG2;
	


	

	void renderBg(RenderWindow* target);
	void animBG(RenderWindow* target, Sprite& sprite, int posY, float speed);


	void updateScrolling(RenderWindow* window);

};

#endif // 