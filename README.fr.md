# Project SM - Moteur de Jeu Bullet Hell

## Table des Matières

- [Description](#description)
- [Fonctionnalités](#fonctionnalités)
- [Lancer l'application](#lancer-lapplication)
- [Compiler l'application](#compiler-lapplication)
	- [Utilisation de VScode](#utilisation-de-vscode)
	- [Utilisation de CMake](#utilisation-de-cmake)
- [Auteurs](#auteurs)


## Description

Project SM est un moteur de jeu bullet hell développé en utilisant la bibliothèque raylib en C++. Il sert de prototype/démonstration, qui sera éventuellement utilisé pour développer un jeu complet. Actuellement, il n'y a qu'un mode de jeu démo (debug), composé d'un niveau et d'une série de phases mettant en avant les capacités du moteur et démontrant différents motifs de tir et de mouvement des ennemis.

## Fonctionnalités

- **Object Pooling :** <br>
Toutes les entités du jeu sont instanciées dès le début du jeu et sont réutilisées et gérées via un gestionnaire de pool, ce qui assure des performances fluides.
- **Machines à États Finis du Joueur :**
Les animations du joueur varient en fonction de son état (Tir, mouvement, Inactif...). De plus, le joueur peut avoir plusieurs états simultanément (par exemple : se déplacer et tirer). Plusieurs automates sont utilisées pour gérer les états du joueur et leurs animations associées.
- **Détection de Collisions :**
Système de détection de collisions pour vérifier les interactions entre les projectiles, les ennemis et le joueur.
- **Motifs de Tir/Mouvement des Ennemis Personnalisables :**
Les ennemis peuvent avoir différents motifs de tir et de mouvement. De plus, de nouveaux motifs peuvent être créés en étendant ou en combinant des motifs existants.
- **Design Modulaire :**
Une architecture hautement modulaire qui permet l'ajout ou la modification facile de fonctionnalités, telles que l'ajout de nouveaux types de projectiles et d'ennemis, de nouveaux motifs de tir et de mouvement (voir ci-dessus), ainsi que l'ajout de nouveaux modes de jeu avec des phases et des stages uniques.
- **Arrière-plans Parallaxes :**
Améliore la profondeur visuelle avec des arrière-plans en défilement parallaxe. Des couches d'images d'arrière-plan se déplacent à des vitesses différentes pour simuler un effet 3D.

## Lancer l'application

Un fichier game.zip contenant une version fonctionnelle de game.exe est fourni. Il suffit d'extraire le fichier dans le répertoire racine, puis de cliquer sur game.exe pour exécuter l'application.

## Compiler et lancer l'application
Notez que ce projet n'a été testé que sous Windows. Il est très probable qu'il ne soit pas possible de le compiler sur une autre plateforme.

### Prérequis
- Raylib
- w64devkit
- CMake (Optionnel)
- Git (Optionnel)

### Dans VScode

Ce projet a été réalisé en utilisant vscode. Adaptez simplement les fichiers json .vscode (launch.json et tasks.json) pour correspondre à la configuration de w64devkit sur votre appareil (principalement "compilerPath", "miDebuggerPath" et "command").

Ensuite, lancez simplement le projet en utilisant le type de compilation souhaité (Debug ou Run).

### En utilisant CMake

Alternativement, il est possible de compiler le projet en utilisant CMake :

Créez un répertoire de build, puis naviguez dedans :
```bash
mkdir build
cd build
```

Une fois dans le répertoire de build, exécutez CMake avec les arguments suivants en fonction 
du type de compilation souhaité:
```bash
cmake -G "MinGW Makefiles" .. -DCMAKE_BUILD_TYPE=Debug
# OU BIEN
cmake -G "MinGW Makefiles" .. -DCMAKE_BUILD_TYPE=Run
```
D'après mes propres testes, il faut exécuter la commande deux fois pour générer le makefile.

Si tout se passe bien, un fichier Make sera créé dans le répertoire de build. Il ne reste plus qu'à taper la commande suivante dans la console :
```bash
make
```

Un fichier game.exe sera créé dans le répertoire de build. 
**Vous devez placer le game.exe dans le répertoire racine du projet, sinon les assets ne seront pas chargés une fois avoir lancer le jeu.**

## Auteurs

- **Auteur:** Ted Herambert
