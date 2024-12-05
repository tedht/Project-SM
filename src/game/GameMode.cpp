#include "GameMode.h"
#include "Game.h"
#include "../entity/enemy/Enemy.h"
#include "../entity/_pattern/FiringPattern.h"
#include "../entity/_pattern/MovementPattern.h"

GameMode::GameMode(Game* game) : game(game)
{
}

void GameMode::HandleInput()
{
	if(IsKeyPressed(KEY_K)) nextPhase();
	if(IsKeyPressed(KEY_J)) previousPhase();
	if(IsKeyPressed(KEY_R)) resetPhase();	
}

void GameMode::nextStage()
{
	if (game->getStage() != Stage::COUNT) 
	{
        game->setStage(static_cast<Stage>(static_cast<int>(game->getStage()) + 1));
		game->setPhase(Phase::ONE);
		Init();
    }
}

void GameMode::nextPhase()
{
	if (game->getPhase() != Phase::COUNT) 
	{
        game->setPhase(static_cast<Phase>(static_cast<int>(game->getPhase()) + 1));
		Init();
    }
	else 
	{
		nextStage();
	}
}

void GameMode::previousStage()
{
	if (game->getStage() != Stage::ONE) 
	{
        game->setStage(static_cast<Stage>(static_cast<int>(game->getStage()) - 1));
		game->setPhase(Phase::ONE);
		Init();
    }
}

void GameMode::previousPhase()
{
	if (game->getPhase() != Phase::ONE) 
	{
        game->setPhase(static_cast<Phase>(static_cast<int>(game->getPhase()) - 1));
		Init();
    }
}

void GameMode::resetPhase()
{
	game->ClearEntities(false);
	Init();
}

Stage GameMode::getStage() { return game->getStage(); }
Phase GameMode::getPhase() { return game->getPhase(); }

DebugMode::DebugMode(Game *game) : GameMode(game)
{
}

void DebugMode::Init()
{
	GenericEnemy1* ge1;

	//StarFP* starFP;
	SpinFP* spinFP;

	CircularMP* circularMP;

	switch (game->getStage())
	{
	/* ******* */
	/* STAGE 1 */
	/* ******* */

	case Stage::ONE:

	switch (game->getPhase())
	{
	// STAGE 1 PHASE 1
	case Phase::ONE:
	ge1 = game->acquireGenericEnemy1();
	ge1->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::WEST_ROT,
				EnemyConfig::GENERC_1_SPEED);

	spinFP = game->acquireSpinFP();
	spinFP->setRotateSpeed(50.0f);
	spinFP->setSpawnerCount(7);
	ge1->setFiringPattern  (spinFP);

	circularMP = game->acquireCircularMP();
	circularMP->setRadiusY(300.0f);
	circularMP->setCounterClockwise();
	ge1->setMovementPattern(circularMP);

	game->SpawnEnemy(ge1);
	break;
	// STAGE 1 PHASE 2
	case Phase::TWO:

	break;
	default: break;
	}
	break;

	default: break;
	}
}

void DebugMode::Update(float deltaTime)
{
}
