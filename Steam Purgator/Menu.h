#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#ifndef MENU_H
#define MENU_H

class Menu {
public:
    Menu(float width, float height, const std::vector<std::string>& options);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;



private:
    void updateFlechePosition();
    std::vector<sf::Text> menuItems;
    sf::Font font;
    size_t selectedIndex;
    sf::Text fleche;
};


#endif // !1
