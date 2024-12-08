#include <SFML/Graphics.hpp>
#include "Game.h"


using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 600), "Fenêtre SFML");
    srand(static_cast<unsigned>(time(0)));
    Game game;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        game.update(&window);
        game.render(&window);
        
    }


    return 0;
}