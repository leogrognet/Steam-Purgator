#include "Menu.h"
#include "Game.h"

using namespace std;
using namespace sf;

enum class GameState { MainMenu, OptionsMenu, OptionsMenu2, Key, Son, Diff, Niv, Joue, Edit, Quitte };

int main() {


 //   cout << "Listes des erreurs :\n-1 : Police non chargée\n-2 : Musique non chargée\n-3 : Sprite non chargée\n\n";


    RenderWindow window(VideoMode(1920, 1080), "STEAM PURGATOR");

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Tableaux avec les options pour chaque menu
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //MENU PRINCIPAL
    vector<string> mainMenuOptions = { "Jouer", "Options","Editeur" ,"QUITTER" };
    //MENUS D'OPTIONS
    vector<string> optionsMenuOptions = { "Son", "Touches","Difficulter", "PAGE 2" };
    vector<string> optionsMenuOptions2 = { "Choix Niv", "Mode Cheat","RETOUR" };
    //SOUS MENUS
    vector<string> sonMenuOptions = { "Son +", "Son -","RETOUR" };
    vector<string> keyMenuOptions = { "Changer","","","RETOUR" };
    vector<string> diffMenuOptions = { "Facile","Normal","Difficile","RETOUR" };
    vector<string> nivMenuOptions = { "Niv 1","Niv 2","Niv 3","RETOUR" };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Menus (copies pour simple)
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Menu mainMenu(window.getSize().x, window.getSize().y, mainMenuOptions);
    Menu optionsMenu(window.getSize().x, window.getSize().y, optionsMenuOptions);
    Menu optionsMenu2(window.getSize().x, window.getSize().y, optionsMenuOptions2);
    Menu sonMenu(window.getSize().x, window.getSize().y, sonMenuOptions);
    Menu keyMenu(window.getSize().x, window.getSize().y, keyMenuOptions);
    Menu diffMenu(window.getSize().x, window.getSize().y, diffMenuOptions);
    Menu nivMenu(window.getSize().x, window.getSize().y, nivMenuOptions);

    GameState gameState = GameState::MainMenu;
    Game game;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //LOAD DES ASSETS
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Font font;
    if (!font.loadFromFile("asset/textAsset/Crang.ttf")) {
        return -1;
    }
    Font font2;
    if (!font2.loadFromFile("asset/textAsset/Crang.ttf")) {
        return -1;
    }

    Music music;
    if (!music.openFromFile("asset/soundsAsset/musique menu.wav")) {
        return -2;
    }

    Music music2;
    if (!music2.openFromFile("asset/soundsAsset/musique in game.wav")) {
        return -2;
    }

    Texture texture;
    if (!texture.loadFromFile("asset/SpriteAsset/bc menu.png")) {
        return -3;
    }

    Sprite sprite;
    sprite.setTexture(texture);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //AFFICHAGE DE TEXTES
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Text Quitter;
    Quitter.setFont(font);
    Quitter.setString("Retour au menu...");
    Quitter.setCharacterSize(20);
    Quitter.setFillColor(Color::White);
    Quitter.setPosition(10, 10);

    Text Titre;
    Titre.setFont(font2);
    Titre.setString("STEAM PURGATOR");
    Titre.setCharacterSize(32);
    Titre.setFillColor(Color::Black);
    Titre.setOutlineColor(Color::White);
    Titre.setPosition(800, 20);

    Text volume;
    volume.setFont(font);
    volume.setCharacterSize(20);
    volume.setFillColor(Color::White);
    volume.setOutlineColor(Color::Black);
    volume.setPosition(850, 740);


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //DEF TEMPS POUR ECHAP
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Clock escapeHoldTimer;
    bool isHoldingEscape = false;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //BOUCLE PRINCIPALE
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    music.setLoop(true);
    music2.setLoop(true);

    music.play();

    while (window.isOpen()) {

        Event event;
        Settings settings;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                switch (gameState) {

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //MENU PRINCIPAL
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //MENU OPTIONS PAGE 1
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
                            //Gestion volume
                            gameState = GameState::Son;
                        }
                        else if (selectedIndex == 1) {
                            //Gestion des touches
                            gameState = GameState::Key;
                        }
                        else if (selectedIndex == 2) {
                            gameState = GameState::Diff;
                        }
                        else if (selectedIndex == 3) {
                            //Vers Page 2
                            gameState = GameState::OptionsMenu2;
                        }
                    }
                    break;

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //MENU OPTIONS PAGE 2
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                case GameState::OptionsMenu2:
                    if (event.key.code == Keyboard::Up) {
                        optionsMenu2.moveUp();
                    }
                    else if (event.key.code == Keyboard::Down) {
                        optionsMenu2.moveDown();
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        int selectedIndex = optionsMenu2.getSelectedIndex();
                        if (selectedIndex == 0) {
                            gameState = GameState::Niv;
                        }
                        else if (selectedIndex == 1) {
                            cout << "mode de triche";
                        }
                        else if (selectedIndex == 2) {
                            //Retour Menu Principal
                            gameState = GameState::MainMenu;
                        }
                    }
                    break;

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //MENU OPTIONS SON
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
                        else if (selectedIndex == 3) {
                            gameState = GameState::OptionsMenu;
                        }
                    }
                    break;

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //MENU OPTIONS TOUCHES
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
                            settings.redefineKeys(settings, window, font, sprite);
                            gameState = GameState::OptionsMenu;
                        }
                        else if (selectedIndex == 3) {
                            gameState = GameState::OptionsMenu;
                        }
                    }
                    break;

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //MENU OPTIONS DIFFICULTER
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                case GameState::Diff:
                    if (event.key.code == Keyboard::Up) {
                        diffMenu.moveUp();
                    }
                    else if (event.key.code == Keyboard::Down) {
                        diffMenu.moveDown();
                    }
                    else if (event.key.code == Keyboard::Enter) {
                        int selectedIndex = diffMenu.getSelectedIndex();
                        if (selectedIndex == 3) {
                            //Retour Menu Principal
                            gameState = GameState::OptionsMenu;
                        }
                    }
                    break;

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //MENU OPTIONS CHOIX DE NIVEAU
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
                            //Retour Menu Principal
                            gameState = GameState::OptionsMenu;
                        }
                    }
                    break;
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //FIN DE TOUT LES CAS DU MENU
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                default:
                    break;
                }
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       //IN GAME (EDITEUR)
       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (gameState == GameState::Edit) {
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                if (!isHoldingEscape) {
                    isHoldingEscape = true;
                    escapeHoldTimer.restart();
                }
                if (escapeHoldTimer.getElapsedTime().asSeconds() >= 2.0f) {
                    gameState = GameState::MainMenu;
                    music2.stop();
                    music.play();
                    isHoldingEscape = false;
                }
            }
            else {
                isHoldingEscape = false;
            }
        }

        window.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //IN GAME (JEU)
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (gameState == GameState::Joue) {
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                if (!isHoldingEscape) {
                    isHoldingEscape = true;
                    escapeHoldTimer.restart();
                }
                if (escapeHoldTimer.getElapsedTime().asSeconds() >= 2.0f) {
                    gameState = GameState::MainMenu;
                    music2.stop();
                    music.play();
                    isHoldingEscape = false;
                }
            }
            else {
                isHoldingEscape = false;
            }
        }

        window.clear();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //DESSIN DES MENU
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

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

        case GameState::OptionsMenu2:
            window.draw(sprite);
            optionsMenu2.draw(window);
            window.draw(Titre);
            break;

        case GameState::Son:
            window.draw(sprite);
            sonMenu.draw(window);
            window.draw(Titre);
            window.draw(volume);
            break;

        case GameState::Key:
            window.draw(sprite);
            keyMenu.draw(window);
            window.draw(Titre);
            break;

        case GameState::Diff:
            window.draw(sprite);
            diffMenu.draw(window);
            window.draw(Titre);
            break;

        case GameState::Niv:
            window.draw(sprite);
            nivMenu.draw(window);
            window.draw(Titre);
            break;

            //CASES DE CHANGEMENT D'INTERFACE

        case GameState::Joue:
            window.clear(Color::White);
            music.pause();
            if (isHoldingEscape) {
                window.draw(Quitter);
            }
            if (game.run()) {
            }
            break;

        case GameState::Edit:
            window.clear(Color::Blue);
            music.pause();
            if (isHoldingEscape) {
                window.draw(Quitter);
            }
            break;
        default:
            break;
        }

        window.display();
    }

    return 0;
}