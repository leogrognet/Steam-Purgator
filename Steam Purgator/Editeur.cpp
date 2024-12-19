#include "Editeur.h"
Texture* selectedTexture = nullptr;

void edit::ltdraw_ennemieE() {
    for (auto* it : this->EnnemieG)
    {
        it->renderEnemy(page);
        if (typeid(*it) != typeid(RangedEnemy)) {
            it->updateAnim();
        }
    }

}
    
void edit::loadTextureE(map<String, Texture*>& textureMap, const string& key, const string& path)
{
    textureMap[key] = new Texture;
    if (!textureMap[key]->loadFromFile(path)) {
        cout << "ERROR::Could not load texture: " << path << endl;
    }

}
void edit::initPlayer() {
   this->loadTextureE(this->PlayerpE, "barreVie", "asset/SpriteAsset/barre_de_vie.png");
    this->loadTextureE(this->PlayerpE, "perso", "asset/SpriteAsset/Perso stu.png");
    this->loadTextureE(this->PlayerpE, "NbMissile", "asset/SpriteAsset/NbMissile.png");
    this->loadTextureE(this->PlayerpE, "NbLaser", "asset/SpriteAsset/Nblaser.png");
    this->loadTextureE(this->PlayerpE, "NbBouclier", "asset/SpriteAsset/NbBouclier.png");
    this->loadTextureE(this->PlayerpE, "NbBombe", "asset/SpriteAsset/NbBombe.png");
    this->playerEd = make_unique<Player>(PlayerpE["perso"], PlayerpE["barreVie"], PlayerpE["NbMissile"], PlayerpE["NbLaser"], PlayerpE["NbBouclier"], PlayerpE["NbBombe"], 200, 2.0f, 2.0f, 500, 500, 10.f, 54, 30, 54, 30);
}
void edit::initP() {
    this->loadTextureE(this->PlayerpE, "boulet", "asset/SpriteAsset/boulet de canon.png");
    this->loadTextureE(this->PlayerpE, "laser", "asset/SpriteAsset/laser.png");
    this->loadTextureE(this->PlayerpE, "missile", "asset/SpriteAsset/missile.png");
    this->loadTextureE(this->PlayerpE, "bouclier", "asset/SpriteAsset/bouclier.png");
    this->loadTextureE(this->PlayerpE, "bombe", "asset/SpriteAsset/Bombe.png");
    this->playerLaser = make_unique<Laser>(PlayerpE["laser"], 1.0f, 1.0f, this->playerEd->getPos().x + this->playerEd->getBounds().width, this->playerEd->getPos().y + this->playerEd->getBounds().height / 2, this->playerEd->getSprite(), 3.0f);
    this->playerShield = make_unique<Shield>(PlayerpE["bouclier"], 1.0f, 1.0f, this->playerEd->getPos().x + this->playerEd->getBounds().width, this->playerEd->getPos().y + this->playerEd->getBounds().height / 2);

    //Texture pour l'ennemi

    this->loadTextureE(this->EnemypE, "boulet", "asset/SpriteAsset/boulet de canon.png");
    this->loadTextureE(this->EnemypE, "bombe", "asset/SpriteAsset/Bombe.png");
    this->loadTextureE(this->EnemypE, "flame", "asset/SpriteAsset/flame.png");
}



void edit::initMunE() {
    this->loadTextureE(this->Muntxt, "bombeMunition", "asset/SpriteAsset/mun Bombe.png");
    this->loadTextureE(this->Muntxt, "laserMunition", "asset/SpriteAsset/mun laser.png");
    this->loadTextureE(this->Muntxt, "missileMunition", "asset/SpriteAsset/mun missile.png");
    this->loadTextureE(this->Muntxt, "bouclierMunition", "asset/SpriteAsset/mun bouclier.png");

}
void edit::inittxtE() {
    this->loadTextureE(this->enemyTexturesE, "Avion", "asset/SpriteAsset/Avion.png");
    this->loadTextureE(this->enemyTexturesE, "Gargouille", "asset/SpriteAsset/gargouille.png");
    this->loadTextureE(this->enemyTexturesE, "Dirigeable Ennemi", "asset/SpriteAsset/Dirigeable ennemie.png");
    this->loadTextureE(this->enemyTexturesE, "Boss_1", "asset/SpriteAsset/boss.png");
    this->loadTextureE(this->enemyTexturesE, "flame", "asset/SpriteAsset/flame.png");
}
void edit::initBG() {

    this->loadTextureE(this->BGtxt, "Tour", "asset/SpriteAsset/Tour.png");
    this->loadTextureE(this->BGtxt, "1stMapVide", "asset/SpriteAsset/Map vide2.png");
    this->loadTextureE(this->BGtxt, "Nuage1", "asset/SpriteAsset/nuage.png");
    this->loadTextureE(this->BGtxt, "Nuage2", "asset/SpriteAsset/nuage lv 2.png");
    this->loadTextureE(this->BGtxt, "BG1", "asset/SpriteAsset/BackGround back.png");
    this->loadTextureE(this->BGtxt, "BG2", "asset/SpriteAsset/BackGround back.png");
    this->levelBGE = make_unique<setBG>(this->BGtxt["Tour"], this->BGtxt["1stMapVide"], this->BGtxt["Nuage1"], this->BGtxt["Nuage2"], this->BGtxt["BG1"], this->BGtxt["BG2"], page);

}
void edit::initallE()
{
    this->initPlayer();
    this->initMunE();
    this->initP();
    this->inittxtE();
    this->initBG();
}
void edit::spawnEnemyEditG() {

        this->EnnemieG.push_back(new CloseRangeEnemy(

            this->enemyTexturesE["Gargouille"], 2.0f, 2.0f, Mouse::getPosition().x - (enemyTexturesE["Gargouille"]->getSize().x/5), Mouse::getPosition().y - (enemyTexturesE["Gargouille"]->getSize().y ), false, 10.f, Vector2f(10, 100),
            100, 100, 100, 100));
}
void edit::spawnEnemyEditA() {

    this->EnnemieG.push_back(new RangedEnemy(

        this->enemyTexturesE["Avion"], 1.5f, 1.5f, Mouse::getPosition().x - (enemyTexturesE["Avion"]->getSize().x / 2), Mouse::getPosition().y - (enemyTexturesE["Avion"]->getSize().y), false, 10.f
    ));
}
void edit::spawnEnemyEditD() {
    this->EnnemieG.push_back(new BigEnemy(
        this->enemyTexturesE["Dirigeable Ennemi"], 3.0f, 3.0f, Mouse::getPosition().x - (enemyTexturesE["Dirigeable Ennemi"]->getSize().x / 2), Mouse::getPosition().y - (enemyTexturesE["Dirigeable Ennemi"]->getSize().y+20), false, 10.f, 1.5f,
        47, 31, 47, 31
    ));

}
void edit::spawnEnemyEditB() {
    this->EnnemieG.push_back(new Boss_1(
        this->enemyTexturesE["Boss_1"], 2.0f, 2.0f, Mouse::getPosition().x - (enemyTexturesE["Boss_1"]->getSize().x / 6), Mouse::getPosition().y - (enemyTexturesE["Dirigeable Ennemi"]->getSize().y*9), true, 1.0f, 274, 273, 274, 273
    ));

}
void edit::Memsuppr() {
    // Nettoyer les ennemis
    this->EnnemieG.erase(
        std::remove_if(
            this->EnnemieG.begin(),
            this->EnnemieG.end(),
            [](BigEnemy* enemy) {
                if (enemy->isMarkedForRemoval()) {
                    delete enemy;
                    return true;
                }
                return false;
            }),
        this->EnnemieG.end()
    );

    // Nettoyer les projectiles du joueur
    this->allPlayerProjectilesE.erase(
        std::remove_if(
            this->allPlayerProjectilesE.begin(),
            this->allPlayerProjectilesE.end(),
            [](Projectile* projectile) {
                if (projectile->isMarkedForRemoval()) {
                    delete projectile;
                    return true;
                }
                return false;
            }),
        this->allPlayerProjectilesE.end()
    );

    // Nettoyer les projectiles ennemis
    this->allEnemyProjectilesE.erase(
        std::remove_if(
            this->allEnemyProjectilesE.begin(),
            this->allEnemyProjectilesE.end(),
            [](Projectile* projectile) {
                if (projectile->isMarkedForRemoval()) {
                    delete projectile;
                    return true;
                }
                return false;
            }),
        this->allEnemyProjectilesE.end()
    );

    // Nettoyer les Munitions
    this->allAmmoE.erase(
        std::remove_if(
            this->allAmmoE.begin(),
            this->allAmmoE.end(),
            [](Ammunition* ammos) {
                if (ammos->isMarkedForRemoval()) {
                    delete ammos;
                    return true;
                }
                return false;
            }),
        this->allAmmoE.end()
    );
}

void edit::updateInputE() {
    this->playerEd->movement(page);

    if (this->playerEd->attack() == 1 && this->playerEd->canAttack())
    {
        this->allPlayerProjectilesE.push_back(new Projectile(PlayerpE["boulet"],
            5.0f,
            5.0f,
            this->playerEd->getBounds().left + this->playerEd->getBounds().width,
            this->playerEd->getBounds().top + (this->playerEd->getBounds().height / 2),
            1.f + this->playerEd->getSpeed(), 10
        )
        );
        cout << "coucou la team";
    }
    if (this->playerEd->attack() == 2) {
        switch (currentWeapon) {
        case 1:
            if (this->playerEd->canAttack() && this->playerEd->weaponCount["missileUse"] > 0) {
                this->allPlayerProjectilesE.push_back(new Missile(PlayerpE["missile"], 1.0f, 1.0f, this->playerEd->getSprite().getPosition().x, this->playerEd->getSprite().getPosition().y, 1.f + this->playerEd->getSpeed(), 63, 21, 63, 21, 20.f));
                this->playerEd->weaponCount["missileUse"] -= 1;
                cout << this->playerEd->weaponCount["missileUse"] << endl;
            }
            break;
        case 2:
            if (this->playerEd->weaponCount["laserUse"] > 0) {
                this->playerLaser->setActive(true);
                this->playerEd->weaponCount["laserUse"] -= 1;
            }
            break;

        case 3:
            if (this->playerEd->weaponCount["shieldUse"] > 0) {
                this->playerShield->setActive(true);
                this->playerEd->weaponCount["shieldUse"] -= 1;
            }
            break;
        }
    }
    else {
        this->playerLaser->setActive(false);
        this->playerShield->setActive(false);
    }


    if (this->playerEd->attack() == 3) {
        if (this->playerEd->attack() == 3 && playerEd->canAttack()) {
            currentWeapon++;
            if (currentWeapon > 3) {
                currentWeapon = 1;
            }

        }

    }
}


void edit::updatebE() {
    for (auto boss : EnnemieG) {
        Boss_1* boss1 = dynamic_cast<Boss_1*>(boss);

        if (boss1) { // Si le cast est réussi, boss est un Boss_1
            cout << boss1->getHealth() << endl;
            boss1->updateSelf(page);
            if (boss1->deltaAttackTime.asSeconds() > 1 && boss1->isShooting) {


                int angle = 180;
                int speedFire = 4.0f;
                this->allEnemyProjectilesE.push_back(new FlameBall(EnemypE["flame"], 5.0f, 5.0f, boss1->getPos().x + 20, boss1->getPos().y + 150, speedFire, angle, 20));
                this->allEnemyProjectilesE.push_back(new FlameBall(EnemypE["flame"], 5.0f, 5.0f, boss1->getPos().x + 20, boss1->getPos().y + 150, speedFire, angle - 20, 20));
                this->allEnemyProjectilesE.push_back(new FlameBall(EnemypE["flame"], 5.0f, 5.0f, boss1->getPos().x + 20, boss1->getPos().y + 150, speedFire, angle - 40, 20));
                this->allEnemyProjectilesE.push_back(new FlameBall(EnemypE["flame"], 5.0f, 5.0f, boss1->getPos().x + 20, boss1->getPos().y + 150, speedFire, angle + 20, 20));
                this->allEnemyProjectilesE.push_back(new FlameBall(EnemypE["flame"], 5.0f, 5.0f, boss1->getPos().x + 20, boss1->getPos().y + 150, speedFire, angle + 40, 20));
                boss1->deltaAttack.restart();
            }


             

            if (boss1->getHealth() < 0) {
                this->isBossKilledE = true;
                boss1->markForRemoval();
            }

            // Gérer les collisions
            if (boss1->getBounds().intersects(this->playerEd->getBounds())) {
                if (this->playerShield->active) {
                    this->playerEd->setHp(this->playerEd->getHp());
                }
                else {
                    this->playerEd->loseHp(10);
                }
            }
        }

        if (this->isBossKilledE) {
            boss->markForRemoval();
        }
    }
}
void edit::updateAmmoE() {
    for (auto Ammo : allAmmoE) {
        Ammo->updateSelf();
        if (Ammo->sprite.getPosition().y > page->getSize().y) {
            Ammo->markForRemoval();
        }
        if (Ammo->sprite.getGlobalBounds().intersects(this->playerEd->getSprite().getGlobalBounds())) {
            switch (Ammo->getAmmo())
            {
            case 1:
                this->playerEd->weaponCount["missileUse"] += Ammo->getAmmoMax();
                Ammo->markForRemoval();
                break;
            case 2:
                this->playerEd->weaponCount["laserUse"] += Ammo->getAmmoMax();
                Ammo->markForRemoval();
                break;
            case 3:
                this->playerEd->weaponCount["shieldUse"] += Ammo->getAmmoMax();
                Ammo->markForRemoval();
                break;
            case 4:
                this->playerEd->weaponCount["bombeUse"] += Ammo->getAmmoMax();
                Ammo->markForRemoval();
                break;
            }
        }
    }
}
void edit::updateEnemyE() {
    for (auto enemies : EnnemieG) {
        enemies->updateSelf(page);


        // Gérer les attaques ennemies
        if (enemies->canAttack() && typeid(*enemies) != typeid (CloseRangeEnemy) && typeid(*enemies) != typeid (Boss_1)) {
            this->allEnemyProjectilesE.push_back(new Projectile(EnemypE["boulet"],
                5.0f, 5.0f,
                enemies->getBounds().left,
                (enemies->getBounds().top + (enemies->getBounds().height / 2)),
                -(enemies->getSpeed() + 10.f), enemies->getDamage()
            ));
        }

        // Collision joueur <-> ennemi
        if (enemies->getBounds().intersects(this->playerEd->getBounds()) && !this->playerShield->active && typeid(*enemies) != typeid (Boss_1)) {
            this->playerEd->loseHp(enemies->getDamage());
            cout << this->playerEd->getHp() << endl;
            enemies->markForRemoval();
        }
        else if (enemies->getBounds().intersects(this->playerEd->getBounds()) && this->playerShield->active && typeid(*enemies) != typeid (Boss_1)) {
            enemies->markForRemoval();
        }
        if (enemies->sprite.getGlobalBounds().width + enemies->sprite.getPosition().x < 0  && typeid(*enemies) != typeid (Boss_1)) {
            enemies->markForRemoval();
        }
        if (enemies->getHealth() <= 0) {
            enemies->markForRemoval();
        }

        // Collision projectiles joueur <-> ennemi
        for (auto projectiles = this->allPlayerProjectilesE.begin(); projectiles != this->allPlayerProjectilesE.end(); ++projectiles) {
            if ((*projectiles)->getBounds().intersects(enemies->getBounds())) {
                enemies->setHealth(enemies->getHealth() - (*projectiles)->getDamage());
                (*projectiles)->markForRemoval();

            }
        }
        if (this->playerLaser->getSprite().getGlobalBounds().intersects(enemies->getBounds()) && this->playerLaser->active) {
            enemies->setHealth(enemies->getHealth() - this->playerLaser->getDamage());
        }
        if (enemies->isMarkedForRemoval()) {
            int spawnAmmo = rand() % 3;
            int randomShield = rand() % 100;
            int randomLaser = rand() % 100;
            int randomMissile = rand() % 100;
            int randomBomb = rand() % 100;
            this->score += enemies->enemyScorePoints;
            switch (spawnAmmo) {
            case 0:

                if (randomShield < 10) {
                    this->allAmmoE.push_back(new Ammunition(Muntxt["missileMunition"], 1.0f, 1.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 1));
                }
            case 1:

                if (randomLaser < 10) {
                    this->allAmmoE.push_back(new Ammunition(Muntxt["laserMunition"], 2.0f, 2.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 2));

                }
            case 2:

                if (randomMissile < 10) {
                    this->allAmmoE.push_back(new Ammunition(Muntxt["bouclierMunition"], 1.0f, 1.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 3));

                }
                //case 3:

                    //if (randomBomb < 10) {
                        //this->allAmmo.push_back(new Ammunition(AmmoTexture["bombeMunition"], 1.0f, 1.0f, enemies->getPos().x, enemies->getPos().y, 1.0f, 4));

                    //}
            }
        }
    }
}
void edit::updateProjectileE() {
    for (auto projectiles : allPlayerProjectilesE) {
        if (typeid (*projectiles) == typeid (Projectile)) {
            projectiles->updateSelf();
            if (projectiles->getBounds().left + projectiles->getBounds().width > page->getSize().x) {
                projectiles->markForRemoval();
            }
            else if (projectiles->getBounds().left + projectiles->getBounds().width < 0.f) {
                projectiles->markForRemoval();
            }
        }
        else if (typeid(*projectiles) == typeid(Missile)) {
            // Trouver l'ennemi le plus proche
            BigEnemy* closestEnemy = nullptr;
            float closestDistance = numeric_limits<float>::max();

            for (auto enemy : EnnemieG) {
                float distance = std::sqrt(
                    pow(enemy->getSprite().getPosition().x - projectiles->getBounds().left, 2) +
                    pow(enemy->getSprite().getPosition().y - projectiles->getBounds().top, 2));

                if (distance < closestDistance) {
                    closestDistance = distance;
                    closestEnemy = enemy;
                }
            }

            // Si un ennemi le plus proche est trouvé, mettre à jour le missile
            if (closestEnemy) {
                projectiles->updateSelf(closestEnemy->getSprite());
                projectiles->isClosest = true;
            }
            else
            {
                projectiles->updateSelf(Sprite());
            }
        }

    }


    for (auto enemyProjectile : allEnemyProjectilesE) {
        if (typeid(*enemyProjectile) == typeid(Projectile)) {
            enemyProjectile->updateSelf();

            if (enemyProjectile->getBounds().left + enemyProjectile->getBounds().width > page->getSize().x) {
                enemyProjectile->markForRemoval();
            }
            else if (enemyProjectile->getBounds().left + enemyProjectile->getBounds().width < 0.f) {
                enemyProjectile->markForRemoval();
            }
            else if (enemyProjectile->getBounds().intersects(this->playerEd->getBounds())) {
                enemyProjectile->markForRemoval();
                this->playerEd->loseHp(10);
            }

        }
        else if (typeid(*enemyProjectile) == typeid(FlameBall)) {
            FlameBall* flameball = dynamic_cast<FlameBall*>(enemyProjectile);
            if (flameball) {
                flameball->updateSelf();
                if (flameball->getBounds().intersects(this->playerEd->getBounds())) {
                    flameball->markForRemoval();
                    this->playerEd->loseHp(10);
                }
            }

        }
    }

}
void edit::updatePlayerE() {
    this->playerLaser->followPlayer(this->playerEd->getSprite());
    this->playerShield->followPlayer(this->playerEd->getSprite());
    this->playerEd->update(page);
    this->playerEd->getHp();
    String Score(to_string(this->score));
    ScoreText.setString("Score:" + Score);
    if (this->playerEd->getHp() <= 0) {

    }
}
void edit::updateBgE() {
    this->levelBGE->updateScrolling(page);
}
void edit::updateE() {
    this->updateAmmoE();
    this->updatePlayerE();
    this->updateInputE();
    this->updateProjectileE();
    this->updateEnemyE();
    this->updateBgE();

    
     this->updatebE();
     this->Memsuppr();
}
void edit::render() {
   page->clear(Color::White);

   this->levelBGE->renderBg(page);

   this->playerEd->render(*page);



    for (auto* it : this->allPlayerProjectilesE)
    {

        it->renderProjectile(page);

    }
    for (auto* it : this->allEnemyProjectilesE)
    {
        it->renderProjectile(page);
    }


    for (auto* it : this->EnnemieG)
    {

        it->renderEnemy(page);
    }

    for (auto* it : this->allAmmoE)
    {

        it->renderAmmo(page);
    }






    this->playerLaser->renderProjectile(page);
    this->playerShield->renderProjectile(page);

    page->display();
}
void edit::edition() {


    this->edit::page = new RenderWindow(VideoMode(1920, 1080), "Editeur de niveau");
    this->page->setFramerateLimit(60);

    this->initallE();

    Texture texture_map;
    if (!texture_map.loadFromFile("asset\\SpriteAsset\\Map vide.png")) {
        cout << "impossible charger le bc";
    }
    Sprite Lmap;
    Lmap.setTexture(texture_map);




    Font police;
    if (!police.loadFromFile("asset/textAsset/Huggo.otf")) {
        cout << "IMPOSSIBLE DE CHARGER LE GAME OVER";
    }


    Text Bt1, Bt2, Bt3, Bt4, Bt5, Bt6;


    //Bouton Gros ennemie
    Bt1.setFont(police);
    Bt1.setString("Ennemie facile");
    Bt1.setCharacterSize(20);
    Bt1.setPosition(Vector2f(100.f, 30.f));
    Bt1.setFillColor(Color::Black);
    Bt1.setStyle(Text::Bold);

    //Bouton Ennemie moyen
    Bt2.setFont(police);
    Bt2.setString("Ennemie moyen");
    Bt2.setCharacterSize(20);
    Bt2.setPosition(Vector2f(400.f, 30.f));
    Bt2.setFillColor(Color::Black);
    Bt2.setStyle(Text::Bold);


    Bt3.setFont(police);
    Bt3.setString("Gros ennemie");
    Bt3.setCharacterSize(20);
    Bt3.setPosition(Vector2f(700.f, 30.f));
    Bt3.setFillColor(Color::Black);
    Bt3.setStyle(Text::Bold);


    Bt4.setFont(police);
    Bt4.setString("Boss");
    Bt4.setCharacterSize(20);
    Bt4.setPosition(Vector2f(1000.f, 30.f));
    Bt4.setFillColor(Color::Black);
    Bt4.setStyle(Text::Bold);

    Bt5.setFont(police);
    Bt5.setString("Retour Menu");
    Bt5.setCharacterSize(20);
    Bt5.setPosition(Vector2f(1200.f, 30.f));
    Bt5.setFillColor(Color::Black);
    Bt5.setStyle(Text::Bold);

    Bt6.setFont(police);
    Bt6.setString("Lancer la partie");
    Bt6.setCharacterSize(20);
    Bt6.setPosition(Vector2f(1500.f, 30.f));
    Bt6.setFillColor(Color::Black);
    Bt6.setStyle(Text::Bold);



    while (page->isOpen()) {
        Event event;

        while (page->pollEvent(event)) {
            if (event.type == Event::Closed)
                page->close();

        }

        if (enemyTexturesE["Gargouille"] == nullptr) {
            cout << "vide" << endl;
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (Mouse::getPosition().x > 100 and Mouse::getPosition().x < 380 and Mouse::getPosition().y > 60 and Mouse::getPosition().y < 88) {
                edit::E_RangedEnemy = true;
                edit::E_CloseRangeEnemy = false;
                edit::E_BigEnemy = false;
                edit::E_Boss = false;
                edit::Rt_menu = false;
            }
            if (Mouse::getPosition().x > 400 and Mouse::getPosition().x < 680 and Mouse::getPosition().y > 60 and Mouse::getPosition().y < 88) {
                edit::E_CloseRangeEnemy = true;
                edit::E_RangedEnemy = false;
                edit::E_BigEnemy = false;
                edit::E_Boss = false;
                edit::Rt_menu = false;
            }
            if (Mouse::getPosition().x > 700 and Mouse::getPosition().x < 965 and Mouse::getPosition().y > 60 and Mouse::getPosition().y < 88) {

                edit::E_BigEnemy = true;
                edit::E_CloseRangeEnemy = false;
                edit::E_RangedEnemy = false;
                edit::E_Boss = false;
                edit::Rt_menu = false;
            }
            if (Mouse::getPosition().x > 1000 and Mouse::getPosition().x < 1080 and Mouse::getPosition().y > 60 and Mouse::getPosition().y < 88) {

                edit::E_Boss = true;
                edit::E_CloseRangeEnemy = false;
                edit::E_RangedEnemy = false;
                edit::E_BigEnemy = false;
                edit::Rt_menu = false;
            }
            if (Mouse::getPosition().x > 1200 and Mouse::getPosition().x < 1440 and Mouse::getPosition().y > 60 and Mouse::getPosition().y < 88) {

                edit::Rt_menu = true;
                edit::E_CloseRangeEnemy = false;
                edit::E_RangedEnemy = false;
                edit::E_BigEnemy = false;
                edit::E_Boss = false;
            }
            if (Mouse::getPosition().x > 1500 and Mouse::getPosition().x < 1820 and Mouse::getPosition().y > 60 and Mouse::getPosition().y < 88) {

                edit::lancement = true;
                edit::Rt_menu = false;
                edit::E_CloseRangeEnemy = false;
                edit::E_RangedEnemy = false;
                edit::E_BigEnemy = false;
                edit::E_Boss = false;
                //voir suite pour balancer game.run ou bien activer un bool defini dans le h qui serait appeler dans le main avec un if 
            }
            if (E_RangedEnemy == true)
            {
                if (clickCount[0] < 1) {
                    spawnClick.restart();
                }
                clickCount[0]++;

                Bt1.setFillColor(Color::Red);
                spawnClickTime = spawnClick.getElapsedTime();
                if (Mouse::isButtonPressed(Mouse::Left) && spawnClickTime.asSeconds() > 0.5f) {

                    startSpawn = Eclock.getElapsedTime();

                    if (startSpawn.asSeconds() > 0.5f) {
                        spawnEnemyEditA();
                        Eclock.restart();
                        spawnClick.restart();
                    }
                }
            }
            if (E_RangedEnemy == false )
            {
                Bt1.setFillColor(Color::Black);
                if (clickCount[0] > 0 ) {
                    clickCount[0] = 0;
                }
            }

            //
            if (E_CloseRangeEnemy == true)
            {

                if (clickCount[1] < 1) {
                    spawnClick.restart();
                }
                clickCount[1]++;

                Bt2.setFillColor(Color::Red);
                spawnClickTime = spawnClick.getElapsedTime();
                if (Mouse::isButtonPressed(Mouse::Left) && spawnClickTime.asSeconds() > 0.5f) {

                    startSpawn = Eclock.getElapsedTime();

                    if (startSpawn.asSeconds() > 0.5f) {
                        spawnEnemyEditG();
                        Eclock.restart();
                        spawnClick.restart();
                    }
                }

            }
            if (E_CloseRangeEnemy == false)
            {
                Bt2.setFillColor(Color::Black);
                if (clickCount[1] > 0) {
                    clickCount[1] = 0;
                }
            }
            //



            if (E_BigEnemy == true)
            {
                if (clickCount[2] < 1) {
                    spawnClick.restart();
                }
                clickCount[2]++;

                Bt3.setFillColor(Color::Red);
                spawnClickTime = spawnClick.getElapsedTime();
                if (Mouse::isButtonPressed(Mouse::Left) && spawnClickTime.asSeconds() > 0.5f) {

                    startSpawn = Eclock.getElapsedTime();

                    if (startSpawn.asSeconds() > 0.5f ) {
                        spawnEnemyEditD();
                        Eclock.restart();
                        spawnClick.restart();
                    }
                }
             
            }
            if (E_BigEnemy == false)
            {
                Bt3.setFillColor(Color::Black);
                clickCount[2] = 0;
            }
            //



            if (E_Boss == true)
            {
                if (clickCount[3] < 1) {
                    spawnClick.restart();
                }
                clickCount[3]++;

                Bt4.setFillColor(Color::Red);
                spawnClickTime = spawnClick.getElapsedTime();
                if (Mouse::isButtonPressed(Mouse::Left) && spawnClickTime.asSeconds() > 0.5f) {

                    startSpawn = Eclock.getElapsedTime();

                    if (startSpawn.asSeconds() > 0.5f) {
                        spawnEnemyEditB();
                        Eclock.restart();
                        spawnClick.restart();
                    }
                }

            }
            if (E_Boss == false)
            {
                Bt4.setFillColor(Color::Black);
                clickCount[3] = 0;
            }
            //

            if (Rt_menu == true)
            {
                Bt5.setFillColor(Color::Red);
                page->close();


            }
            if (Rt_menu == false)
            {
                Bt5.setFillColor(Color::Black);
            }

            if (lancement == true)
            {
                Bt6.setFillColor(Color::Red);
                this->initallE();
                while (true)
                {
                    
                    this->updateE();
                    this->render();
                    if(this->playerEd->getHp() <= 0){
                        this->page->close();
                    }
                    

                }
            }





        }











        cout << EnnemieG.size() << endl;
        page->draw(Lmap);
        page->draw(Bt1);
        page->draw(Bt2);
        page->draw(Bt3);
        page->draw(Bt4);
        page->draw(Bt5);
        page->draw(Bt6);
        this->ltdraw_ennemieE();
        page->display();
    }
};
