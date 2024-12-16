#pragma once

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include <string>
#include <sstream> // Pour convertir les noms des touches en chaînes
#include <iostream>

using namespace std;
using namespace sf;

class Menu {
public:
    Menu(float width, float height, const vector<string>& options);

    void draw(RenderWindow& window);

    void moveUp();
    void moveDown();

    void handleMouseClick(Vector2i mousePos);

    int getSelectedIndex() const;

private:

    void updateFlechePosition();

    vector<Text> menuItems;
    Font font;
    size_t selectedIndex;
    Text fleche;
};

class Settings {
public:
    Settings();

    void setCustomKey(const string& action, Keyboard::Key key);
    void redefineKeys(Settings& settings, RenderWindow& window, const Font& font, const Sprite& background);

    void increaseVolume(); // Pour augmenter de 10
    void decreaseVolume(); // Pour diminuer de 10
    int getVolume() const;

private:

    int volume; // Volume de 0 à 100

    map<string, Keyboard::Key> customKeys;

};
#endif // MENU_H