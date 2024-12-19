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
// Bombe init
struct Bombecrea
{
    Sprite sprtBombe;
    Bombecrea(const Texture& texture_bombe, Vector2f positionB) {

        sprtBombe.setTexture(texture_bombe);
        sprtBombe.setPosition(positionB);



    }

    void déplacementB(float cord_bombex, float cord_bombey) {
        sprtBombe.move(cord_bombex, cord_bombey);
    }



};
void pregame() {

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pre-Game");
    //Texture Bc chargement
    Texture BC, BCquitter, BClancer;
    if (!BC.loadFromFile("bc start.png") or
        !BCquitter.loadFromFile("bouton quitter bc.png") or
        !BClancer.loadFromFile("bouton lancerbc.png")
        ) {
        cout << endl << "IMPOSSIBLE DE CHARGER LES COEURS" << endl;
    }

    Sprite BC_M, BC_quitter, BC_lancer;
    BC_M.setTexture(BC);
    BC_M.setPosition(Vector2f(0.f, 0.f));
    BC_quitter.setTexture(BCquitter);
    BC_quitter.setPosition(Vector2f(750.f, 440.f));
    BC_lancer.setTexture(BClancer);
    BC_lancer.setPosition(Vector2f(530.f, 340.f));

    // police chagement
    Font Pre_GameL, Pre_GameQ;
    if (!Pre_GameL.loadFromFile("huggo\\Huggo.otf") or
        !Pre_GameQ.loadFromFile("huggo\\Huggo.otf")) {
        cout << "IMPOSSIBLE DE CHARGER LE GAME OVER";
    }
    Text Lancer, Quitter;


    //Bouton lancer
    Lancer.setFont(Pre_GameL);
    RectangleShape LancerR(Vector2f(820.f, 70.f));
    LancerR.setFillColor(Color(255, 255, 255, 0));
    LancerR.setPosition(Vector2f(530.f, 360.f));
    Lancer.setString("LANCER UNE PARTIE");
    Lancer.setCharacterSize(50);
    Lancer.setPosition(550.f, 340);
    Lancer.setFillColor(Color::White);
    Lancer.setStyle(Text::Bold);


    //Bouton quitter
    Quitter.setFont(Pre_GameQ);
    RectangleShape QuitterR(Vector2f(355.f, 70));//255 par 70
    QuitterR.setFillColor(Color(245, 225, 215, 0));
    QuitterR.setPosition(Vector2f(750.f, 440.f));
    Quitter.setString("QUITTER");
    Quitter.setCharacterSize(50);
    Quitter.setPosition(770.f, 440);
    Quitter.setFillColor(Color::White);
    Quitter.setStyle(Text::Bold);



    //musique pregame

    SoundBuffer musique_pregame;
    Sound musique_pregamE;
    musique_pregamE.setBuffer(musique_pregame);
    if (!musique_pregame.loadFromFile("music pregame.wav")) {
        cout << endl << "IMPOSSIBLE DE CHARGER LA MUSIQUE" << endl;
    }
    musique_pregamE.play();
    musique_pregamE.setLoop(true);


    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

        }

        if (Mouse::isButtonPressed(Mouse::Left)) {//quitter
            if (Mouse::getPosition().x > 750 and Mouse::getPosition().x < 1055 and Mouse::getPosition().y >470 and Mouse::getPosition().y < 540) {
                window.close();
                Pregamestart = false;
            }
            //lancer
            if (Mouse::getPosition().x > 537 and Mouse::getPosition().x < 1357 and Mouse::getPosition().y >360 and Mouse::getPosition().y < 430) {
                window.close();
                Pregamestart = true;
            }
        }




        window.draw(BC_M);
        window.draw(BC_quitter);
        window.draw(BC_lancer);
        window.draw(QuitterR);
        window.draw(LancerR);
        window.draw(Quitter);
        window.draw(Lancer);
        window.display();

    }
}



void Jeux() {
    int lvdiff = 5;
    int nb_bombe = 0;
    int vie = 3;
    int score = 0;

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mousi la souris");

    //initi image
    Texture texture_souris, texture_map, texture_bombe, texture_bc;
    if (!texture_souris.loadFromFile("Souris perso.png") or
        !texture_map.loadFromFile("Map.png") or
        !texture_bombe.loadFromFile("bombe_poison.png") or
        !texture_bc.loadFromFile("bc main map.png")
        ) {
        cout << endl << "IMPOSSIBLE DE CHARGER LES IMAGE" << endl;
    }


    //Perso cré
    Souris SourisJ(texture_souris, Vector2f(850.f, 775.f));


    // MAP creé

    Sprite Map, bc;
    Map.setTexture(texture_map);
    Map.setPosition(Vector2f(600.f, 40.f));//c'est du 600 de largue pour du 800 de haut avec une épaisseur de bordure de 32 en bas
    bc.setTexture(texture_bc);

    // autre truc pour les bombes
    vector<Bombecrea>SupB;
    Clock bombetimer;
    const float bombeInterval = 760.0f;



    //musique
    SoundBuffer musique_jeux;
    Sound musique_jeuxE;
    musique_jeuxE.setBuffer(musique_jeux);
    if (!musique_jeux.loadFromFile("musica.wav")) {
        cout << endl << "IMPOSSIBLE DE CHARGER LA MUSIQUE" << endl;
    }
    musique_jeuxE.play();
    musique_jeuxE.setLoop(true);



    // coeur affichage

    Texture Coeur1, Coeur2, Coeur3;
    if (!Coeur1.loadFromFile("coeur.png") or
        !Coeur2.loadFromFile("coeur.png") or
        !Coeur3.loadFromFile("coeur.png")
        ) {
        cout << endl << "IMPOSSIBLE DE CHARGER LES COEURS" << endl;
    }
    Sprite Coeur_1, Coeur_2, Coeur_3;
    Coeur_1.setTexture(Coeur1);
    Coeur_1.setPosition(Vector2f(860.f, 70.f));
    Coeur_2.setTexture(Coeur2);
    Coeur_2.setPosition(Vector2f(875.f, 70.f));
    Coeur_3.setTexture(Coeur3);
    Coeur_3.setPosition(Vector2f(885.f, 70.f));

    //Score
    Font Pol;
    if (!Pol.loadFromFile("huggo\\Huggo.otf")) {
        cout << "IMPOSSIBLE DE CHARGER LE GAME OVER";
    }
    Text scoreJ;
    scoreJ.setFont(Pol);
    scoreJ.setCharacterSize(50);
    scoreJ.setFillColor(Color::Red);
    scoreJ.setStyle(Text::Bold);
    scoreJ.setPosition(1100.f, 840.f);
    scoreJ.setString("0");


    //Boucle fenetre
    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        // déplacement de la petite souris + sortie de carte
        Sleep(3);
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (SourisJ.Mousi.getPosition().x < 1152) {
                SourisJ.déplacementSD(+5.f, 0.f);


            }
        }
        Sleep(3);
        if (Keyboard::isKeyPressed(Keyboard::Left)) {

            if (SourisJ.Mousi.getPosition().x > 625) {
                SourisJ.déplacementSD(-5.f, 0.f);
            }
        }


        // génère une position pour la bombe puis l'incère 
        if (bombetimer.getElapsedTime().asMilliseconds() > bombeInterval and nb_bombe <= lvdiff) {
            vector<float> positionsdX = { 625.f, 735.f, 848.f, 958.f, 1065.f };
            float poserandomX = positionsdX[rand() % positionsdX.size()];
            SupB.emplace_back(texture_bombe, Vector2f(poserandomX, 64.f));
            bombetimer.restart();
            nb_bombe += 1;
        }

        // Destruction bombe
        for (auto bombe = SupB.begin(); bombe != SupB.end(); ) {
            if (score < 20) {
                bombe->déplacementB(0.f, 2.f);
            }
            if (score >= 20) {
                bombe->déplacementB(0.f, 4.f);
                int lvdiff = 8;
            }
            bombe->déplacementB(0.f, 2.f);
            if (bombe->sprtBombe.getPosition().y >= 703) {
                bombe = SupB.erase(bombe);
                nb_bombe--;
                score++;
                String ScoreDj(to_string(score));
                scoreJ.setString(ScoreDj);
            }
            else {
                window.draw(bombe->sprtBombe);
                ++bombe;
            }
        }
        for (auto bombe = SupB.begin(); bombe != SupB.end();) {
            if (bombe->sprtBombe.getGlobalBounds().intersects(SourisJ.Mousi.getGlobalBounds())) {
                bombe = SupB.erase(bombe);
                nb_bombe--;
                vie--;
            }
            else {
                ++bombe;
            }
        }
        if (vie == 2) {
            Coeur_3.setColor(Color(255, 255, 255, 0));
        }
        if (vie == 1) {
            Coeur_2.setColor(Color(255, 255, 255, 0));
        }
        if (vie == 0) {
            Coeur_1.setColor(Color(255, 255, 255, 0));
        }
        //bouton quitter in game
        if (Mouse::isButtonPressed(Mouse::Left)) {//quitter
            if (Mouse::getPosition().x > 600 and Mouse::getPosition().x < 770 and Mouse::getPosition().y >870 and Mouse::getPosition().y < 915) {
                window.close();
            }
        }

        Font Quitter_pp;
        if (!Quitter_pp.loadFromFile("huggo\\Huggo.otf")) {
            cout << "IMPOSSIBLE DE CHARGER LE GAME OVER";
        }
        Text QuitterLP;
        QuitterLP.setFont(Quitter_pp);
        RectangleShape hitboxQt(Vector2f(170.f, 40));//255 par 70
        hitboxQt.setFillColor(Color(245, 225, 215, 0));
        hitboxQt.setPosition(Vector2f(600.f, 850.f));
        QuitterLP.setString("QUITTER");
        QuitterLP.setCharacterSize(25);
        QuitterLP.setPosition(600.f, 850.f);
        QuitterLP.setFillColor(Color::Black);
        QuitterLP.setStyle(Text::Bold);




        //condition defaite
        bool GAME_OVER = false;
        Font Pol;
        if (!Pol.loadFromFile("huggo\\Huggo.otf")) {
            cout << "IMPOSSIBLE DE CHARGER LE GAME OVER";
        }
        Text lose;
        lose.setFont(Pol);
        if (vie <= 0) {
            lose.setString("GAME OVER");
            lose.setCharacterSize(100);
            lose.setPosition(450.f, WINDOW_HEIGHT / 2);
            lose.setFillColor(Color::Red);
            lose.setStyle(Text::Bold);
            GAME_OVER = true;
            window.draw(lose);
            window.display();
        }

        window.clear();
        //MAP aff
        window.draw(bc);
        window.draw(Map);


        //Perso aff
        window.draw(SourisJ.Mousi);

        //bombe aff
        for (const auto& Bombecrea : SupB) {
            window.draw(Bombecrea.sprtBombe);
        }

        //Coeur
        window.draw(Coeur_1);
        window.draw(Coeur_2);
        window.draw(Coeur_3);

        // game over
        window.draw(lose);

        //Score aff
        window.draw(scoreJ);

        //quitter la parie 
        window.draw(hitboxQt);
        window.draw(QuitterLP);
        //affichage comp0
        window.display();

        //fin de partie 
        if (GAME_OVER == true) {
            this_thread::sleep_for(std::chrono::seconds(5));

            window.close();
        }
    }
}
int main() {
    pregame();
    if (Pregamestart == true) {
        Jeux();
    }
    return 0;
}