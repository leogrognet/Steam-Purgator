#include "menu.h"

using namespace std;
using namespace sf;

Menu::Menu(float width, float height, const vector<string>& options)
    : selectedIndex(0) {
    if (!font.loadFromFile("C:/Users/tburton/Desktop/asset/Daydream.ttf")) {}

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

int Menu::getSelectedIndex() const {
    return selectedIndex;
}

void Menu::updateFlechePosition() {
    fleche.setPosition(menuItems[selectedIndex].getPosition().x - 40,
        menuItems[selectedIndex].getPosition().y - 5);
}

Settings::Settings() {
    customKeys["MoveUp"] = Keyboard::Z;
    customKeys["MoveDown"] = Keyboard::S;
    customKeys["MoveLeft"] = Keyboard::Q;
    customKeys["MoveRight"] = Keyboard::D;
    customKeys["Action1"] = Keyboard::LAlt;
    customKeys["Action2"] = Keyboard::Num1;
    customKeys["Action3"] = Keyboard::Num2;
}

void Settings::setCustomKey(const string& action, Keyboard::Key key) {
    customKeys[action] = key;
}

void Settings::redefineKeys(Settings& settings, RenderWindow& window, const Font& font, const Sprite& background) {
    vector<pair<string, string>> actions = {
        {"MoveUp", "Monter"}, //1
        {"MoveDown", "Descendre"}, //2
        {"MoveLeft", "Gauche"}, //3
        {"MoveRight", "Droite"}, //4
        {"Action1", "Action 1"}, //5
        {"Action2", "Action 2"}, //6
        {"Action3", "Action 3"} //7
    };

    for (const auto& actionPair : actions) {
        const string& action = actionPair.first;       // Nom interne
        const string& description = actionPair.second; // Desc affichée

        Text instruction;
        instruction.setFont(font);
        instruction.setString("Appuyez sur une touche pour : " + description);
        instruction.setCharacterSize(25);
        instruction.setFillColor(Color::White);
        instruction.setPosition(500, 400);

        bool keyAssigned = false;
        while (!keyAssigned) {
            Event event;
            window.clear();
            window.draw(instruction);
            window.display();

            while (window.pollEvent(event)) {
                if (event.type == Event::KeyPressed) {

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

    Text confirmation;
    confirmation.setFont(font);
    confirmation.setString("Touches redefinies");
    confirmation.setCharacterSize(25);
    confirmation.setFillColor(Color::Green);
    confirmation.setOutlineColor(Color::Black);
    confirmation.setPosition(500, 500);

    window.clear();
    window.draw(confirmation);
    window.display();

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
