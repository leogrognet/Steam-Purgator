#include "Player.h"
#include "Enemy.h"
#include "menu.h"

using namespace std;
using namespace sf;

enum class GameState { MainMenu, OptionsMenu, Joue, Quitte };

int main() 
{
    RenderWindow window(VideoMode(1920, 1080), "STEAM PURGATOR");

    Texture texture;
    if (!texture.loadFromFile("C:/Users/tburton/Desktop/asset/bc_menu2.png")) {
        return -1;
    }

    Sprite sprite;
    sprite.setTexture(texture);

/*
DEF DU PLAYER ET DES ENNEMIS
    Player player;

    player.playerSprite.setFillColor(Color::Red);
    player.playerSprite.setPosition(0, 0);
    player.playerSprite.setSize(Vector2f(10.0f, 10.0f));
    player.speed = 0.01;
    player.Keybind[player.Direction::Up] = Keyboard::Z;
    player.Keybind[player.Direction::Down] = Keyboard::S;
    player.Keybind[player.Direction::Left] = Keyboard::Q;
    player.Keybind[player.Direction::Right] = Keyboard::D;

    Enemy enemy;

    enemy.enemySprite.setFillColor(Color::Red);
    enemy.enemySprite.setPosition(0, 0);
    enemy.enemySprite.setSize(Vector2f(10.0f, 10.0f));
    enemy.speed = 0.01;
*/

    std::vector<std::string> mainMenuOptions = { "Lancer", "Options", "Quitter" };
    std::vector<std::string> optionsMenuOptions = { "Choix Stage", "Son / Light", "Debug Mode", "Retour" };
    Menu mainMenu(window.getSize().x, window.getSize().y, mainMenuOptions);
    Menu optionsMenu(window.getSize().x, window.getSize().y, optionsMenuOptions);
    GameState gameState = GameState::MainMenu;

    Font font;
    if (!font.loadFromFile("C:/Users/tburton/Desktop/asset/Daydream.ttf")) {
        return -1; //Faut créer un chemin d'acces fixe parce que c'est chiant de le changer h24
    }
    /*
    Font font;
    if (!font.loadFromFile("C:/Users/tburton/Desktop/asset/Crang.ttf")) {
        return -2; //Faut créer un chemin d'acces fixe parce que c'est chiant de le changer h24
    }
    */
    Text quittingMessage;
    quittingMessage.setFont(font);
    quittingMessage.setString("En train de quitter...");
    quittingMessage.setCharacterSize(20);
    quittingMessage.setFillColor(Color::White);
    quittingMessage.setPosition(10, 10);

    Text Titre;
    Titre.setFont(font);
    Titre.setString("STEAM PURGATOR");
    Titre.setCharacterSize(40);
    Titre.setFillColor(Color::White);
    Titre.setOutlineColor(Color::Black);
    Titre.setPosition(960 , 50);

    Clock escapeHoldTimer;
    bool isHoldingEscape = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                switch (gameState) {
                case GameState::MainMenu:
                    if (event.key.code == Keyboard::Up) {
                        mainMenu.moveUp();
                    }
                    else if (event.key.code == Keyboard::Down) {
                        mainMenu.moveDown();
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        int selectedIndex = mainMenu.getSelectedIndex();
                        if (selectedIndex == 0) {
                            gameState = GameState::Joue;
                        }
                        else if (selectedIndex == 1) {
                            gameState = GameState::OptionsMenu;
                        }
                        else if (selectedIndex == 2) {
                            gameState = GameState::Quitte;
                            window.close();
                        }
                    }
                    break;
                case GameState::OptionsMenu:
                    if (event.key.code == Keyboard::Up) {
                        optionsMenu.moveUp();
                    }
                    else if (event.key.code == Keyboard::Down) {
                        optionsMenu.moveDown();
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        int selectedIndex = optionsMenu.getSelectedIndex();
                        if (selectedIndex == 3) {
                            gameState = GameState::MainMenu;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        }

        if (gameState == GameState::Joue) {
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                if (!isHoldingEscape) {
                    isHoldingEscape = true;
                    escapeHoldTimer.restart();
                }
                if (escapeHoldTimer.getElapsedTime().asSeconds() >= 2.0f) {
                    gameState = GameState::MainMenu;
                    isHoldingEscape = false;
                }
            }
            else {
                isHoldingEscape = false;
            }
        }

        window.clear();

        switch (gameState) {
        case GameState::MainMenu:
            window.draw(sprite);
            mainMenu.draw(window);
            window.draw(Titre);
            break;
        case GameState::OptionsMenu:
            window.draw(sprite);
            optionsMenu.draw(window);
            window.draw(Titre);
            break;
        case GameState::Joue:
            window.clear(sf::Color::Blue);
            if (isHoldingEscape) {
                window.draw(quittingMessage);
            }
            break;
        default:
            break;
        }
        window.display();
    }
    return 0;
}