#include "Player.h"
#include "Enemy.h"
#include "menu.h"
#include"Game.h"

using namespace std;
using namespace sf;

enum class GameState { MainMenu, OptionsMenu, Son, Joue, Quitte };

int main() {
    RenderWindow window(VideoMode(1920, 1080), "STEAM PURGATOR");

    Texture texture;
    if (!texture.loadFromFile("C:/Users/tburton/Desktop/asset/bc_menu2.png")) {
        return -1;
    }

    Sprite sprite;
    sprite.setTexture(texture);

    vector<string> mainMenuOptions = { "Lancer", "Options", "Quitter" };
    vector<string> optionsMenuOptions = { "Choix Stage", "Son", "Debug Mode", "Retour" };
    vector<string> sonMenuOptions = { "Son +", "Son -", "Retour","Volume Total plus tard };
    Menu mainMenu(window.getSize().x, window.getSize().y, mainMenuOptions);
    Menu optionsMenu(window.getSize().x, window.getSize().y, optionsMenuOptions);
    Menu sonMenu(window.getSize().x, window.getSize().y, sonMenuOptions);
    GameState gameState = GameState::MainMenu;

    Font font;
    if (!font.loadFromFile("C:/Users/tburton/Desktop/asset/Daydream.ttf")) {
        return -1; // Chemin fixe recommandé
    }

    Text quittingMessage;
    quittingMessage.setFont(font);
    quittingMessage.setString("Retour au menu...");
    quittingMessage.setCharacterSize(20);
    quittingMessage.setFillColor(Color::White);
    quittingMessage.setPosition(10, 10);

    Text Titre;
    Titre.setFont(font);
    Titre.setString("   STEAM\nPURGATOR");
    Titre.setCharacterSize(25);
    Titre.setFillColor(Color::White);
    Titre.setOutlineColor(Color::Black);
    Titre.setPosition(890, 20);

    Text volume;
    volume.setFont(font);
    volume.setCharacterSize(20);
    volume.setFillColor(Color::White);
    volume.setOutlineColor(Color::Black);
    volume.setPosition(850,740);

    Clock escapeHoldTimer;
    bool isHoldingEscape = false;

    while (window.isOpen()) {
        Event event;
        Settings settings;
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
                        if (selectedIndex == 0) {
                            //choix du stage
                        }
                        else if (selectedIndex == 1) {
                            gameState = GameState::Son;
                        }
                        else if (selectedIndex == 2) {
                            //mode Triche
                        }
                        else if (selectedIndex == 3) {
                            gameState = GameState::MainMenu;
                        }
                    }
                    break;

                case GameState::Son:

                    if (event.key.code == Keyboard::Up) {
                        sonMenu.moveUp();
                    }
                    else if (event.key.code == Keyboard::Down) {
                        sonMenu.moveDown();
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        int selectedIndex = sonMenu.getSelectedIndex();
                        if (selectedIndex == 0) {
                            // Augmenter le volume de 10
                                settings.increaseVolume(); // Augmente le volume de 10
                            cout << settings.getVolume();
                        }
                        else if (selectedIndex == 1) {
                            // Diminuer le volume de 10
                            settings.decreaseVolume();
                            cout << settings.getVolume();   
                        }
                        else if (selectedIndex == 2) {
                            gameState = GameState::OptionsMenu;
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

        case GameState::Son:
            window.draw(sprite);
            sonMenu.draw(window);
            window.draw(Titre);
            window.draw(volume);
            break;

        case GameState::Joue: {
            Game game(&window);
            if(game.run(&window)){}
            else { gameState = GameState::MainMenu; break; }    
            if (isHoldingEscape) {
                window.draw(quittingMessage);
            }
            break;
        }
        default:
            break;
        }
        window.display();
    }
    return 0;
}
