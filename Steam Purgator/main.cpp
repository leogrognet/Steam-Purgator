#include "menu.h"

using namespace std;
using namespace sf;

enum class GameState { MainMenu, OptionsMenu, Key, Son, Niv, Joue, Edit, Quitte, Pause };

int main() {

    cout << "Listes des erreurs :\n-1 : Police non chargée\n-2 : Musique non chargée\n-3 : Sprite non chargée\n";
    RenderWindow window(VideoMode(1920, 1080), "STEAM PURGATOR");

    vector<string> mainMenuOptions = { "Jouer", "Options","Editeur" ,"QUITTER" };
    vector<string> optionsMenuOptions = { "Son", "Touches","Choix NIv", "RETOUR" };
    vector<string> sonMenuOptions = { "Son +", "Son -","Voir son","RETOUR" };
    vector<string> keyMenuOptions = { "Changer","RETOUR"};
    vector<string> nivMenuOptions = { "Niv 1","Niv 2","Niv 3","RETOUR" };
    vector<string> pauseMenuOptions = { "Continuer","Quitter" };

    Menu mainMenu(window.getSize().x, window.getSize().y, mainMenuOptions);
    Menu optionsMenu(window.getSize().x, window.getSize().y, optionsMenuOptions);
    Menu sonMenu(window.getSize().x, window.getSize().y, sonMenuOptions);
    Menu keyMenu(window.getSize().x, window.getSize().y, keyMenuOptions);
    Menu nivMenu(window.getSize().x, window.getSize().y, nivMenuOptions);
    Menu pauseMenu(window.getSize().x, window.getSize().y, pauseMenuOptions);

    GameState gameState = GameState::MainMenu;

    Font font; if (!font.loadFromFile("C:/Users/tburton/Desktop/asset/Daydream.ttf")) { return -1; }
    Music music; if (!music.openFromFile("C:/Users/tburton/Desktop/asset/musique_menu.wav")) { return -2; }
    Music music2; if (!music2.openFromFile("C:/Users/tburton/Desktop/asset/musique_ingame.wav")) { return -2; }
    Texture texture; if (!texture.loadFromFile("C:/Users/tburton/Desktop/asset/bc_menu2.png")) { return -3; }
    Texture texture2; if (!texture2.loadFromFile("C:/Users/tburton/Desktop/asset/bc_menu.png")) { return -3; }

    Sprite sprite; sprite.setTexture(texture);
    Sprite sprite2; sprite2.setTexture(texture2);

    sprite2.setPosition(500, 100);

    Text Titre;Titre.setFont(font);Titre.setString("STEAM\nPURGATOR");Titre.setCharacterSize(25);Titre.setFillColor(Color::White);Titre.setOutlineColor(Color::Black);Titre.setPosition(869, 16);

    bool isHoldingEscape = false;

    music.setLoop(true);
    music2.setLoop(true);

    music.play();

    int volume2 = 50;
    GameState previousState = GameState::MainMenu;
    std::map<std::string, sf::Keyboard::Key> customKeys;

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
                            music.stop();
                            music2.play();
                            gameState = GameState::Joue;
                        }
                        else if (selectedIndex == 1) {
                            gameState = GameState::OptionsMenu;
                        }
                        else if (selectedIndex == 2) {
                            music.stop();
                            music2.play();
                            gameState = GameState::Edit;
                        }
                        else if (selectedIndex == 3) {
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
                            gameState = GameState::Son;
                        }
                        else if (selectedIndex == 1) {
                            gameState = GameState::Key;
                        }
                        else if (selectedIndex == 2) {
                            gameState = GameState::Niv;
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
                            volume2 += 5;
                            if (volume2 > 100) {
                                volume2 = 100;
                            }
                        }
                        else if (selectedIndex == 1) {
                            volume2 -= 5;
                            if (volume2 < 0) {
                                volume2 = 0;
                            }

                        }
                        else if (selectedIndex == 2) {
                            cout << "Volume : " << volume2 << " %" << endl;
                        }
                        else if (selectedIndex == 3) {
                            gameState = GameState::OptionsMenu;
                        }
                    }
                    if (volume2 < 0) {
                        volume2 = 0;
                    }
                    else if (volume2 > 100) {
                        volume2 = 100;
                    }
                    break;
                case GameState::Key:

                    if (event.key.code == Keyboard::Up) {
                        keyMenu.moveUp();
                    }
                    else if (event.key.code == Keyboard::Down) {
                        keyMenu.moveDown();
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        int selectedIndex = keyMenu.getSelectedIndex();
                        if (selectedIndex == 0) {

                            settings.redefineKeys(settings, window, font,sprite2);
                            for (size_t i = 0; i < keyMenuOptions.size(); ++i) {
                                Text keyText;
                                keyText.setFont(font);
                                keyText.setString(keyMenuOptions[i] + ": ");
                                keyText.setCharacterSize(20);
                                keyText.setFillColor(Color::White);
                                keyText.setPosition(900, 100 + i * 30);
                                window.draw(keyText);
                            }
                            break;
                        }

                        else if (selectedIndex == 1) {
                            gameState = GameState::OptionsMenu;
                        }
                    }
                    break;
                
                case GameState::Niv:
                    if (event.key.code == Keyboard::Up) {
                        nivMenu.moveUp();
                    }
                    else if (event.key.code == Keyboard::Down) {
                        nivMenu.moveDown();
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        int selectedIndex = nivMenu.getSelectedIndex();
                        if (selectedIndex == 0) {
                        }
                        else if (selectedIndex == 3) {
                            gameState = GameState::OptionsMenu;
                        }
                    }
                    break;
                case GameState::Joue:
                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                        previousState = gameState;
                        gameState = GameState::Pause;
                    }
                    break;

                case GameState::Edit:
                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                        previousState = gameState;
                        gameState = GameState::Pause;
                    }
                    break;

                case GameState::Pause:
                    if (event.key.code == Keyboard::Up) {
                        pauseMenu.moveUp();
                    }
                    else if (event.key.code == Keyboard::Down) {
                        pauseMenu.moveDown();
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        int selectedIndex = pauseMenu.getSelectedIndex();
                        if (selectedIndex == 0) {
                            gameState = previousState;
                        }
                        else if (selectedIndex == 1) {
                            gameState = GameState::MainMenu;
                            music2.stop();
                            music.play();
                        }
                    }
                    break;
    
                default:
                    break;
                }
            }
        }
        //DESSIN DES MENU
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
            break;
        case GameState::Key:
            window.draw(sprite);
            //window.draw(sprite2);
            keyMenu.draw(window);
            window.draw(Titre);
            break;
        case GameState::Niv:
            window.draw(sprite);
            nivMenu.draw(window);
            window.draw(Titre);
            break;
        case GameState::Joue:
            window.clear(Color::White);
            music.pause();
            //if (game.run()) {
            //}
            break;
        case GameState::Edit:
            window.clear(Color::Blue);
            music.pause();
            
            break;
        case GameState::Pause:
            window.draw(sprite2);
            pauseMenu.draw(window);
            break;
        default:
            break;
        }
        window.display();
    }
    return 0;
}
