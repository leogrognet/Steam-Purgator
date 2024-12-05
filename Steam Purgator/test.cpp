#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"


using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 600), "Fenêtre SFML");
    

    Player player();
    
    player.playerSprite.setFillColor(Color::Red);
    player.playerSprite.setPosition(0, 0);
    player.playerSprite.setSize(Vector2f(10.0f,10.0f));
    player.speed= 0.01;
    player.Keybind[player.Direction::Up] = Keyboard::Z;
    player.Keybind[player.Direction::Down] = Keyboard::S;
    player.Keybind[player.Direction::Left] = Keyboard::Q;
    player.Keybind[player.Direction::Right] = Keyboard::D;


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);
        player.movement();
        //if (Keyboard::isKeyPressed(Keyboard::Z)) { player.playerSprite.move(0, 5); }
        window.draw(player.playerSprite);
        window.display();
    }


    return 0;
}