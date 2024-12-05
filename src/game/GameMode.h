#pragma once

#include "GameMode.h"
#include "../../include/constants/gameplay_constants.h"

class Game;

class GameMode
{
protected:
	Game* game;
public:
	GameMode(Game* game);

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void HandleInput();

	void nextStage    ();
	void nextPhase    ();
	void previousStage();
	void previousPhase();
	void resetPhase   ();

	Stage getStage();
	Phase getPhase();

	virtual ~GameMode() = default;
};

/* Debug */
class DebugMode : public GameMode
{
public:
	DebugMode(Game* game);

	void Init();
	void Update(float deltaTime);
};

/* Easy */

/* Medium */

/* Hard */