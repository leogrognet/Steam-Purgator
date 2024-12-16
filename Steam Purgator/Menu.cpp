#include "menu.h"

using namespace std;
using namespace sf;

Menu::Menu(float width, float height, const vector<string>& options)
    : selectedIndex(0) {
    if (!font.loadFromFile("C:/Users/tburton/Desktop/asset/Daydream.ttf")) {
        // Erreur de chargement de la police
    }

    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(20);
        text.setFillColor(i == 0 ? Color::Red : Color::White);
        text.setPosition(width / 2 - text.getLocalBounds().width / 2, height / 5 + i * 170);
        menuItems.push_back(text);
    }

    fleche.setFont(font);
    fleche.setString(">");
    fleche.setFillColor(Color::Yellow);
    updateFlechePosition();
}

void Menu::draw(RenderWindow& window) {
    for (const auto& item : menuItems) {
        window.draw(item);
    }
    window.draw(fleche);
}

void Menu::moveUp() {
    if (selectedIndex > 0) {
        menuItems[selectedIndex].setFillColor(Color::White);
        selectedIndex--;
        menuItems[selectedIndex].setFillColor(Color::Red);
        updateFlechePosition();
    }
}

void Menu::moveDown() {
    if (selectedIndex < menuItems.size() - 1) {
        menuItems[selectedIndex].setFillColor(Color::White);
        selectedIndex++;
        menuItems[selectedIndex].setFillColor(Color::Red);
        updateFlechePosition();
    }
}

void Menu::handleMouseClick(Vector2i mousePos) {
    for (size_t i = 0; i < menuItems.size(); ++i) {
        FloatRect bounds = menuItems[i].getGlobalBounds();
        if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            menuItems[selectedIndex].setFillColor(Color::White);
            selectedIndex = i;
            menuItems[selectedIndex].setFillColor(Color::Red);
            updateFlechePosition();
            break;
        }
    }
}

int Menu::getSelectedIndex() const {
    return selectedIndex;
}

void Menu::updateFlechePosition() {
    fleche.setPosition(menuItems[selectedIndex].getPosition().x - 40,
        menuItems[selectedIndex].getPosition().y - 5);
}

Settings::Settings() : volume(50) {
    customKeys["1"] = Keyboard::A;
    customKeys["2"] = Keyboard::Z;
    customKeys["3"] = Keyboard::E;
    customKeys["4"] = Keyboard::R;
    customKeys["5"] = Keyboard::T;
}

void Settings::increaseVolume() {
    if (volume < 100) {
        volume += 10;
    }
}

void Settings::decreaseVolume() {
    if (volume > 0) {
        volume -= 10;
    }
}

int Settings::getVolume() const {
    return volume;
}

void Settings::setCustomKey(const string& action, Keyboard::Key key) {
    customKeys[action] = key;
}

void Settings::redefineKeys(Settings& settings, RenderWindow& window, const Font& font, const Sprite& background) {
    // Liste des actions et leurs descriptions
    vector<pair<string, string>> actions = {
        {"MoveUp", "Monter"},
        {"MoveDown", "Descendre"},
        {"Confirm", "Confirmer"}
    };

    // Boucle pour redéfinir chaque touche
    for (const auto& actionPair : actions) {
        const string& action = actionPair.first;       // Nom interne de l'action (ex: "MoveUp")
        const string& description = actionPair.second; // Description affichée (ex: "Monter")

        // Afficher l'instruction à l'utilisateur
        Text instruction;
        instruction.setFont(font);
        instruction.setString("Appuyez sur une touche pour : " + description);
        instruction.setCharacterSize(25);
        instruction.setFillColor(Color::White);
        instruction.setPosition(500, 400);

        // Attente de l'appui sur une touche
        bool keyAssigned = false;
        while (!keyAssigned) {
            Event event;
            window.clear();
            window.draw(background); // Afficher le fond
            window.draw(instruction);
            window.display();

            while (window.pollEvent(event)) {
                if (event.type == Event::KeyPressed) {
                    // Assigner la touche à l'action
                    settings.setCustomKey(action, event.key.code);
                    keyAssigned = true;
                }
                else if (event.type == Event::Closed) {
                    window.close();
                    return;
                }
            }
        }
    }

    // Confirmation finale
    Text confirmation;
    confirmation.setFont(font);
    confirmation.setString("Touches redefinies");
    confirmation.setCharacterSize(25);
    confirmation.setFillColor(Color::Green);
    confirmation.setOutlineColor(Color::Black);
    confirmation.setPosition(500, 500);

    window.clear();
    window.draw(background);
    window.draw(confirmation);
    window.display();

    // Pause pour afficher le message de confirmation
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 2.0f) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return;
            }
        }
    }
}