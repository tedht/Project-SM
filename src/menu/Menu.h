#pragma once

#include "MenuState.h"

class Menu {
private:
    MenuState* currentState;

public:    
	Menu();

	void HandleInput();
    void Update();
    void Draw();

	void changeState(MenuState* newState);

	~Menu() = default;
};