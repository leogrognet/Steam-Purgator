#pragma once

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace sf;

class Menu {
public:
    Menu(float width, float height, const vector<string>& options);
    void draw(RenderWindow& window);
    void moveUp();
    void moveDown();
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
private:
    map<string, Keyboard::Key> customKeys;
};
#endif
