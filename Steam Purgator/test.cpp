#include <SFML/Graphics.hpp>
#include "Game.h"


using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 600), "Fenêtre SFML");
    
    Game game;


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);
        game.updatePlayer(game.player, window);
        game.updateProjectile(window);
        window.draw(game.player.playerSprite);
        for (auto& proj : game.allProjectiles)
            window.draw(proj.sprite);
     
        window.display();
    }


    return 0;
}