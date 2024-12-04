#include <iostream>
#include <map>
#include "SFML/Graphics.hpp"



using namespace std;
using namespace sf;

#ifndef GAME_H
#define	GAME_H

class Game {
private :

public:
	void updatePlayer();
	void updateEnemy();
	void updateProjectile();
	void updateConfig();


};


#endif