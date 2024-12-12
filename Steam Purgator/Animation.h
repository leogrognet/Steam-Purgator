#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <thread>
#include <chrono>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
using namespace std;
using namespace sf;
bool Pregamestart = false;
int score = 0;
int anim_updt = 0;
bool laserA = false;
bool bouclierA = false;

class Animation {
private:
public:
    Sprite TourMap;

};

//Perso init
class Souris {
public:
    Sprite Mousi;
    RectangleShape hitboxS;
    Souris(const Texture& texture_souris, Vector2f positionS) {//juste au cas ou positionS c'est la position de la souris 
        Mousi.setTexture(texture_souris);
        Mousi.setPosition(positionS);

        hitboxS.setSize(Vector2f(17.f, 35.f));
        hitboxS.setPosition(positionS);
        hitboxS.setFillColor(Color(255, 255, 255, 0));
    }

    void déplacementSD(float cord_x, float cord_y) {
        Mousi.move(cord_x, cord_y);
        hitboxS.move(cord_x, cord_y);
    }
};

void Jeux() {
    int lvdiff = 5;
    int nb_bombe = 0;
    int vie = 3;
    int score = 0;

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mousi la souris");




    Sprite Map, Gargouille, Boss, Dirigeable, Laser, Tourmap, Bouclier;
    //initi image
    Texture texture_souris, texture_map, texture_gargouille, texture_boss, texture_dirigeable, texture_laser, texture_JxL, texture_tourmap, texture_bouclier;
    if (!texture_souris.loadFromFile("Perso stu simple.png") or
        !texture_map.loadFromFile("Map vide.png") or
        !texture_gargouille.loadFromFile("gargouille.png") or
        !texture_boss.loadFromFile("boss.png") or
        !texture_dirigeable.loadFromFile("Dirigeable ennemie.png") or
        !texture_laser.loadFromFile("Laser.png") or
        !texture_JxL.loadFromFile("Perso stu laser.png") or
        !texture_tourmap.loadFromFile("tour.png") or
        !texture_bouclier.loadFromFile("Bouclier.png")
        ) {
        cout << endl << "IMPOSSIBLE DE CHARGER LES IMAGE" << endl;
    }
    Map.setTexture(texture_map);
    Gargouille.setTexture(texture_gargouille);
    Boss.setTexture(texture_boss);
    Dirigeable.setTexture(texture_dirigeable);
    Laser.setTexture(texture_laser);
    Tourmap.setTexture(texture_tourmap);
    Bouclier.setTexture(texture_bouclier);
    //Perso cré
    Souris SourisJ(texture_souris, Vector2f(850.f, 775.f));
    Vector2f animP(1, 0), animG(1, 0), animB(1, 0), animD(1, 0);

    Tourmap.setPosition(Vector2f(500, 384));
    SourisJ.Mousi.setScale(5.f, 5.f);
    Laser.setScale(2.f, 2.f);
    Bouclier.setScale(4.f, 6.f);

    //Boucle fenetre
    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        // déplacement de la petite souris + sortie de carte
        window.clear();
        Sleep(3);
        if (Keyboard::isKeyPressed(Keyboard::Right)) {

            SourisJ.déplacementSD(+5.f, 0.f);
        }
        Sleep(3);
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            SourisJ.déplacementSD(-5.f, 0.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            SourisJ.déplacementSD(0.f, +5.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            SourisJ.déplacementSD(0.f, -5.f);
        }
        if (Keyboard::isKeyPressed(Keyboard::K)) {
            if (bouclierA == false and laserA == false) {
                SourisJ.Mousi.setTexture(texture_JxL);
                laserA = true;
            }
            if (bouclierA == true) {
                bouclierA = false;
            }


        }
        if (Keyboard::isKeyPressed(Keyboard::B)) {
            if (laserA == false and bouclierA == false) {
                SourisJ.Mousi.setTexture(texture_JxL);
                bouclierA = true;
            }
            if (laserA == true) {
                laserA = false;
            }
        }
        if (SourisJ.Mousi.getPosition().x != Laser.getPosition().x or SourisJ.Mousi.getPosition().y != Laser.getPosition().y) {
            Laser.setPosition(Vector2f(SourisJ.Mousi.getPosition().x + 260, SourisJ.Mousi.getPosition().y + 90));


        }
        if (SourisJ.Mousi.getPosition().x != Bouclier.getPosition().x or SourisJ.Mousi.getPosition().y != Bouclier.getPosition().y) {
            Bouclier.setPosition(Vector2f(SourisJ.Mousi.getPosition().x + 260, SourisJ.Mousi.getPosition().y + 15));


        }
        animP.x++;
        if (animP.x * 54 >= texture_souris.getSize().x) {
            animP.x = 0;
        }
        animG.x++;
        if (animG.x * 100 >= texture_gargouille.getSize().x) {
            animG.x = 0;
        }
        animB.x++;
        if (animB.x * 274 >= texture_boss.getSize().x) {
            animB.x = 0;
        }
        animD.x++;
        if (animD.x * 47 >= texture_dirigeable.getSize().x) {
            animD.x = 0;
        }
        if (Tourmap.getPosition().x <= -347) {
            Tourmap.setPosition(Vector2f(WINDOW_WIDTH + 350, 384));
        }
        if (Tourmap.getPosition().x > -347 and Tourmap.getPosition().x <= WINDOW_WIDTH + 350) {
            Tourmap.setPosition(Vector2f(Tourmap.getPosition().x - 10, 384));

        }
        SourisJ.Mousi.setTextureRect(IntRect(animP.x * 54, animP.y * 30, 54, 30));
        Gargouille.setTextureRect(IntRect(animG.x * 100, animG.y * 100, 100, 100));
        Boss.setTextureRect(IntRect(animB.x * 274, animB.y * 273, 274, 273));
        Dirigeable.setTextureRect(IntRect(animD.x * 47, animD.y * 31, 47, 31));

        //Perso aff
        Boss.setPosition(Vector2f(300.f, 300.f));
        Dirigeable.setPosition(Vector2f(400.f, 600.f));
        window.draw(Map);
        window.draw(Tourmap);
        window.draw(Boss);
        window.draw(Dirigeable);
        window.draw(Gargouille);
        window.draw(SourisJ.Mousi);
        if (laserA == true) {
            window.draw(Laser);
        }
        if (bouclierA == true) {
            window.draw(Bouclier);
        }
        window.display();

    }
};
int main() {
    Jeux();
}