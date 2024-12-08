#include "Menu.h"

    Menu::Menu(float width, float height, const std::vector<std::string>& options)
        : selectedIndex(0) {
        if (!font.loadFromFile("asset/arial.ttf")) {
        }
        for (size_t i = 0; i < options.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(options[i]);
            text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
            text.setPosition(width / 2 - text.getLocalBounds().width / 2, height / 4 + i * 50);
            menuItems.push_back(text);
        }
        fleche.setFont(font);
        fleche.setString(">");
        fleche.setFillColor(sf::Color::Yellow);
        updateFlechePosition();
    }
    void Menu::draw(sf::RenderWindow& window) {
        for (const auto& item : menuItems) {
            window.draw(item);
        }
        window.draw(fleche);
    }
    void Menu::moveUp() {
        if (selectedIndex > 0) {
            menuItems[selectedIndex].setFillColor(sf::Color::White);
            selectedIndex--;
            menuItems[selectedIndex].setFillColor(sf::Color::Red);
            updateFlechePosition();
        }
    }
    void Menu::moveDown() {
        if (selectedIndex < menuItems.size() - 1) {
            menuItems[selectedIndex].setFillColor(sf::Color::White);
            selectedIndex++;
            menuItems[selectedIndex].setFillColor(sf::Color::Red);
            updateFlechePosition();
        }
    }
    int Menu::getSelectedIndex() const {
        return selectedIndex;
    }

    void Menu::updateFlechePosition() {
        fleche.setPosition(menuItems[selectedIndex].getPosition().x - 40,
            menuItems[selectedIndex].getPosition().y);
    }
    
