#include "Menu.h"
#include"Game.h"

enum class GameState { MainMenu, OptionsMenu, Joue, Quitte };

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu principal");
    std::vector<std::string> mainMenuOptions = { "Lancer le jeu", "Options", "Quitter" };
    std::vector<std::string> optionsMenuOptions = { "Option 1", "Option 2", "Option 3", "Option 4", "Retour au menu principal" };
    Menu mainMenu(window.getSize().x, window.getSize().y, mainMenuOptions);
    Menu optionsMenu(window.getSize().x, window.getSize().y, optionsMenuOptions);
    GameState gameState = GameState::MainMenu;
    sf::Font font;
    if (!font.loadFromFile("asset/arial.ttf")) {
        return -1;
    }
    sf::Text quittingMessage;
    quittingMessage.setFont(font);
    quittingMessage.setString("En train de quitter...");
    quittingMessage.setCharacterSize(20);
    quittingMessage.setFillColor(sf::Color::White);
    quittingMessage.setPosition(10, 10);
    sf::Clock escapeHoldTimer;
    bool isHoldingEscape = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (gameState) {
                case GameState::MainMenu:
                    if (event.key.code == sf::Keyboard::Up) {
                        mainMenu.moveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        mainMenu.moveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int selectedIndex = mainMenu.getSelectedIndex();
                        if (selectedIndex == 0) {
                            gameState = GameState::Joue;
                            window.setSize(sf::Vector2u(1024, 768));
                            window.setTitle("Jeu en cours");
                            
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
                    if (event.key.code == sf::Keyboard::Up) {
                        optionsMenu.moveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        optionsMenu.moveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int selectedIndex = optionsMenu.getSelectedIndex();
                        if (selectedIndex == 4) {
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                if (!isHoldingEscape) {
                    isHoldingEscape = true;
                    escapeHoldTimer.restart();
                }
                if (escapeHoldTimer.getElapsedTime().asSeconds() >= 2.0f) {

                    gameState = GameState::MainMenu;
                    window.setSize(sf::Vector2u(800, 600));
                    window.setTitle("Menu principal");
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
            mainMenu.draw(window);
            break;
        case GameState::OptionsMenu:
            optionsMenu.draw(window);
            break;
        case GameState::Joue: {
            Game game;
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