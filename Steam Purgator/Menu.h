#pragma once

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

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
    void increaseVolume(); // Pour augmenter de 10
    void decreaseVolume(); // Pour diminuer de 10        
    int getVolume() const;
    void setCustomKey(const string& action, Keyboard::Key key);
private:
    int volume; // Volume de 0 à 100
};
#endif //MENU.H
