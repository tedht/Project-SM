#include <raylib.h>
#include <algorithm>
#include <array>
#include <iostream>

#include "../include/constants/graphics_constants.h"

#include "menu/Menu.h"
#include "menu/MenuState.h"

int main() 
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sunny man");
    SetTargetFPS(FPS); 

	Menu menu;
    menu.changeState(&GameState::getInstance());

	while (!WindowShouldClose()) 
	{
		menu.HandleInput();
	    menu.Update();
		BeginDrawing();
		menu.Draw();
		EndDrawing();
    }

    CloseWindow();

    return 0;
}