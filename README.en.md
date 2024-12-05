# Project SM - Bullet Hell Game Engine

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Launching the application](#launching-the-application)
- [Compiling the application](#compiling-the-application)
	- [Using VScode](#using-vscode)
	- [Using CMake](#using-cmake)
- [Authors](#authors)


## Description

Project SM is a bullet hell game engine built using the raylib library in C++. It serves as a prototype/demo, 
which will eventually be used to develop a full game. Currently, there is only a demo (debug) game mode, consisting of 1 stage and a series of phases showcasing the engine's capabilities and demonstrating different enemy firing and movement patterns.

## Features

- **Object Pooling:** <br>
All game entties are instaniated at the very start of the game and are reused and managed via a
pool manager which ensures smooth performance.
- **Player Finite State Machines:**
Player animations vary depending on the player state (Firing, moving, Idle...). Moreover, the player can
have multiple states at the same time (ex: Moving and Firing). Multiple Finite State Machines are used to handle
the player states and their associated animations.
- **Collision Detection:**
Collision detection system to check interactions between bullets, enemies, and the player.
- **Customizable Enemy Firing/Movement Patterns**
Enemies can have different movement and firing patterns. Furthermore, new patterns can be created 
by extending or combining existing patterns.
- **Modular Design**
A highly modular architecture that supports easy addition or modification of features, such as
the addition of new bullet and enemy types, new firing and movement patterns (see above), as
well as new gamemodes with unique phases and stages.
- **Parallax Backgrounds:**
Enhance visual depth with parallax scrolling backgrounds. Layers of background images move at different 
speeds to simulate a 3D effect

## Launching the application

To launch the game, click on the provided game.exe located in the root directory of the project.

## Compiling the application
Note that this project has only been tested on Windows. It is most likely not possible
to compile it on any other platform.

### Prerequisites
- Raylib
- w64devkit
- CMake (Optional)
- Git (Optional)

### In VScode

This project was made using vscode. Simply adapt the .vscode json files (launch.json and tasks.json)
to correspond with your devices setup of w64devkit (mainly "compilerPath", "midDebuggerPath" and "command").

Then just run the project using the desired build mode (Debug or Run).

### Using CMake

Alternatively, it is possible to compile the project using CMake:

Create a build directory, then navigate into it:
```bash
mkdir build
cd build
```

Once inside the build directory, run CMake with the following arguments :
```bash
cmake -G "MinGW Makefiles" .. 
```

If all goes well, a Make file will be created in the build directory. All that is
left to do is to type the following in the console :
```bash
make
```

Note that the game.exe will be created in the build directory. 
**You must place the game.exe in the root directory of the project, other wise the assets won't load.**

## Authors

- **Author :** Ted Herambert
