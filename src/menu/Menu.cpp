#include <iostream>

#include "Menu.h"

Menu::Menu() : currentState(nullptr)
{
}

void Menu::HandleInput()
{
	if (currentState != nullptr) 
	{
		currentState->HandleInput(this);
		//std::cout << currentState->getName() << std::endl;
	}
}


void Menu::Update()
{
	if (currentState != nullptr) 
	{
		currentState->Update(this);
		//std::cout << currentState->getName() << std::endl;
	}
}

void Menu::Draw()
{
	if (currentState != nullptr) 
	{
		currentState->Draw();
	}
}

void Menu::changeState(MenuState *newState)
{
	if (currentState != nullptr) 
	{
		currentState->exit();
	}
	
	currentState = newState;

	if (currentState != nullptr) 
	{
		currentState->enter();
	}
}
