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
int Menu::getSelectedIndex() const {
    return selectedIndex;
}
void Menu::updateFlechePosition() {
    fleche.setPosition(menuItems[selectedIndex].getPosition().x - 40,
        menuItems[selectedIndex].getPosition().y - 5);
}
Settings::Settings() : volume(50) {}
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
/*
void Settings::setCustomKey(const string& action, Keyboard::Key key) {
    Touches[action] = key;
}
*/
//2e page avec debug + fenetre + keybind
