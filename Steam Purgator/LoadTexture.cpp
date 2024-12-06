#pragma once
#include "SFML/Graphics.hpp"


sf::Texture textureBlueBird;
int loadTexture(){
	if (!textureBlueBird.loadFromFile("BlueBird.png")) return 0;
}

