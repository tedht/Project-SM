#include "MenuState.h"
#include "Menu.h"
#include "../game/Game.h"

class Menu;

MenuState::MenuState()
{
}

void GameState::HandleInput(Menu *menu)
{
	
	/*
	if(game->isPaused())
		//menu->changeState(&PauseState::getInstance())
		std::cout << "PAUSED" << std::endl;
	else if(game->isGameOver())
		//menu->changeState(&GameOverState::getInstance())
		std::cout << "GAMEOVER" << std::endl;
	else*/
		game->HandleInput();
}

/* MENU STATES */
// GameState
void GameState::Update(Menu* menu)
{
	game->Update();
}

void GameState::Draw()
{
	game->Draw();
}

void GameState::enter()
{
	game->Init();
}

void GameState::exit()
{
}

std::string GameState::getName()
{
	return "GameState";
}

GameState& GameState::getInstance()
{
	static GameState singleton;
	return singleton;
}

GameState::GameState()
{
	game = new Game();
}

GameState::~GameState()
{
	delete game;
}


GameState &GameState::operator=(const GameState &other)
{
	if (this == &other)
		return *this;

	delete game;

	game = new Game(*other.game);

	return *this;
}

