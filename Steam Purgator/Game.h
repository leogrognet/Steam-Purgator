#include <memory>
#include "Projectile.h"
#include "Player.h"




using namespace std;
using namespace sf;

#ifndef GAME_H
#define	GAME_H

class Game {
private :
	Texture *texture;

	vector<Projectile*> allProjectiles;
	unique_ptr<Player> player;


	void initPlayer();
	void initProjectile();

public:
	
	Game();
	virtual ~Game();


	void updatePlayer(RenderWindow& window);
	void updateInput();

	void updateEnemy();
	void updateProjectile(RenderWindow* window);
	void updateCollision(RenderWindow* window);
	void update(RenderWindow* window);

	int count=0;

	void render(RenderWindow* window);

};


#endif