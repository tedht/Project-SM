#pragma once

#include <iostream>

class Menu;
class Game;

class MenuState {
public:
	virtual void HandleInput(Menu* menu) = 0;
    virtual void Update(Menu* menu) = 0;
	virtual void Draw() = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;
	virtual std::string getName() = 0;
    virtual ~MenuState() = default;
protected:
	MenuState();
};

class GameState : public MenuState
{
public:
	void HandleInput(Menu* menu);
	void Update(Menu* menu);
	void Draw();
	void enter();
	void exit();
	std::string getName();

	static GameState& getInstance();
private:
	GameState();
	~GameState();
	GameState(const GameState& other);
	GameState& operator=(const GameState& other);	

	Game* game;
};

/*
class GameOverState : public MenuState
{

}

class MainMenuState : public MenuState
{

}

class PauseState : public MenuState
{

}
*/


