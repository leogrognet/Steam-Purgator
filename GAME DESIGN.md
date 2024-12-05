# **Document de Game Design : Steam Purgator**
---
## **1.Information Générales**

Titre: Steam Purgator

**Genre**: Shoot'em Up / Roguelike
**Style Visuel**: SteamPunk pixel art détaillé
**Plateforme**: Pc
**Public Cible**: Amateur de Shoot'em up nerveux
**Résumé**: 
Dans un univers ou le passé s'entremele aux innovations, des fléaux apparaissent sur terre, invoqué par une organisation souhaitant le chaos pour instaurer un nouvelle ere. Le joueur incarne un vaisseau faisant parti d'une resistance et va devoir défaire ces fleaux parcourant le monde semé d'embûches.

---

## **2. Concept de Base**
- **Gameplay Principal** : Le joueur contrôle un Dirigeable de guerre, détruit des vagues d'ennemis et évite des projectiles pour progresser dans des niveaux générés aléatoirement, au nombre de 4, et peuvent recevoir des bonus passif aléatoire au cours du jeu. 
- **Objectifs** : 
  - Court terme : Avoir le meilleur score en survivant le plus longtemps et en tuant le plus d'ennemis
  - Long Terme :  Compléter les niveaux, vaincre tout les boss
- **Déroulement** :  Le jeu est divisé en plusieurs niveaux, généré aléatoirement avec une difficulté croissante, chacun se terminant par un combat de boss unique.
- **Style de progression** : Défilement horizontal automatique, avec des moments d'arret ou l'on recupère des bonus aléatoire donnant des armes ou des passifs.

---

## **3.Mechaniques de Jeu**

### **3.1. Contrôle du joueur**

- **Déplacement** : Mouvement en 8 direction à l'aide de 4 touches différentes modulable, (Z, Q, S, D) par défaut

- **Tir principal** :
  - Tir automatique en maintenant une touche modulable enfoncé, degat faible
  - Mecanique de coup critique, quand une tir touche une cible chance de faire des degats supplementaire, defini selon un pourcentage, clique gauche de souris par défaut

- **Tir secondaire** :
  - Tir non automatique, en appuyant sur une touche modulable, degat moyen - élevé en fonction du powerup
possibilité de changer de powerup une touche modulable, alt par défaut
nombre limité a 10 missiles, recuperables sur les ennemis, les obstacles ou les colis
  - Clique droit de souris par défaut

### **3.2. Système de Scoring**

- **Ennemi tué** : +100
- **Gros ennemi tué** : +250
- **Boss tué** : +5000
- **Niveau complété** : +10000

- **Multiplicateurs** : 
Au cours des niveaux, plus le joueur avance entre les niveux et plus le score donné par les ennemis tué est élevé
Ennemi tué : Niveau 1: +100 Niveau 2: +150 Niveau 3: +250 Niveau 4: +500;
Gros ennemi tué: Niveau 1: +250 Niveau 2: +300 Niveau 3: +400 Niveau 4: +650;


### **3.3. Power-ups**

- **Liste de powerup possibles** :

    - **Missiles Autoguidé**
    - **Boulets Explosifs**
    - **Tirs Magique**
    - **Bouclier d'immunité**


### **3.4. Power-Up passif** 

-**Branche Alchimie** :
  -Taille d'explosion augmenté pour les Boulets Explosifs
  -Dégats sur la durée augmentée
  -Temps de l'utilisation des Boulets Explosifs diminué

-**Branche Mecanique** :
  -Vitesse de tir augmenté
  -Dégats sur chaque tir augmenté
  -Chance de coup Critique accru 20%
  -Nombre de Missiles Autoguidé augmenté

-**Branche Magique** :
  -Soins accrus sur les tirs magique
  -Temps pour utiliser le laser diminué
  -Temps du Bouclier d'immunité augmenté



### **3.5. Difficulté**
- **Modes de jeu** :
  -Facile: les ennemis meurt en peu de coup et font peu de dégats
  -Normal : Dégats des ennemis accrus et vitesse augmenté
  -Difficile : Plus d’ennemis, tirs plus rapides, vitesse tres rapide
  -Hardcore : Tirs très complexes, erreurs non pardonnées.

---

## **4. Types d'ennemis**
- **Ville de Windercove** : 
  -Dirigeable: ennemis avec beaucoup de vie, lent, avec de gros dégats a distance
  -Avions a helice: Ennemis a vitesse normale, tir rapide, dégats moyen, vie moyenne
  -Gargouille de Métal: Ennemis très rapide, peu de vie, dégats important, ne peux pas tirer

- **Faille de la derniere Chance** :
  -Bateau pirate Volant: ennemis avec beaucoup de vie, lent, avec de gros dégats a distance
  -Jet Volant: Ennemis a vitesse rapide, peu de vie, peu de dégats, tirs tres rapide
  -Sirene Ailée: Ennemis a vitesse moyenne, attaque au corps a corps, vie moyene, degats moyen

---

## **5. Progression et Structure**
### **5.1 Niveaux**
- **1. Niveau 1** :
  - Ville de Windercove
  - Ville Steampunk avec Tour d'horloge et Toiture Victorienne
  - Ennemis: Dirigeable, Avions a helice, Gargouille de Métal 
  - Boss: Grand Dragon de Metal

- **2. Niveau 2** :
  - Faille de la derniere Chance
  - Ennemis: Bateau Pirate volant, Jet Volant, Sirene Ailée
  - Boss: Monstre Tentaculaire



### **5.2 Rythme**
Les niveaux alternent entre moment de combats et moment de pause ou le joueur choisis les Power Up. A chaque fin de boss le score est affiché au joueur et il passe au niveau suivant.

---

## **6.Direction artistique** :
### **6.1 Style Visuel**
  - Pixel Art Simple

### **6.2 Interface utilisateur**
  - Menu De Bouton avec un theme Aerien

---

## **8.Systemes et Outils**
### **8.1 Bibliotheque  utilisée**
  - SFML

---

## **9.Monétisation**
Jeu vendu seul, pas de dlc prévu. 5 euros.

---

## **10.Inspirations**
  - *Hades* : sur le systeme rogue like des bonus passifs aléatoire
  - *R-Type* : sur le scrolling et le principe du shoot them up horizontal

