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
	GenericEnemy2* ge2;

	StraightFP* straightFP;
	TargetedFP* targetedFP;
	StarFP* starFP;
	SpinFP* spinFP;

	LeftRightLoopMP* leftRightLoopMP;
	CircularMP*      circularMP;

	switch (game->getStage())
	{
	/* ******* */
	/* STAGE 1 */
	/* ******* */

	case Stage::ONE:

	switch (game->getPhase())
	{
	/* STAGE 1 PHASE 1 */
	case Phase::ONE:
	ge1 = game->acquireGenericEnemy1();
	ge1->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::SOUTH_ROT,
				EnemyConfig::GENERC_1_SPEED);

	game->SpawnEnemy(ge1);
	break;

	/* STAGE 1 PHASE 2 */
	case Phase::TWO:
	game->ClearEntities(false);
	ge1 = game->acquireGenericEnemy1();
	ge1->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::SOUTH_ROT,
				EnemyConfig::GENERC_1_SPEED);

	straightFP = game->acquireStraightFP();
	ge1->setFiringPattern(straightFP);
	
	game->SpawnEnemy(ge1);
	break;
	/* STAGE 1 PHASE 3 */
	case Phase::THREE:
	game->ClearEntities(false);
	ge1 = game->acquireGenericEnemy1();
	ge1->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::SOUTH_ROT,
				EnemyConfig::GENERC_1_SPEED);

	targetedFP = game->acquireTargetedFP();
	ge1->setFiringPattern(targetedFP);
	
	game->SpawnEnemy(ge1);
	break;
	/* STAGE 1 PHASE 4 */
	case Phase::FOUR:
	game->ClearEntities(false);
	ge1 = game->acquireGenericEnemy1();
	ge1->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::SOUTH_ROT,
				EnemyConfig::GENERC_1_SPEED);

	targetedFP = game->acquireTargetedFP();
	targetedFP->setBulletSpeed(150.0f);
	targetedFP->setShootCooldown(0.25f);
	ge1->setFiringPattern(targetedFP);
	
	game->SpawnEnemy(ge1);
	break;
	/* STAGE 1 PHASE 5 */
	case Phase::FIVE:
	game->ClearEntities(false);
	ge1 = game->acquireGenericEnemy1();
	ge1->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::WEST_ROT,
				EnemyConfig::GENERC_1_SPEED);

	targetedFP = game->acquireTargetedFP();
	ge1->setFiringPattern(targetedFP);

	leftRightLoopMP = game->acquireLeftRightLoopMP();
	ge1->setMovementPattern(leftRightLoopMP);
	
	game->SpawnEnemy(ge1);
	break;
	/* STAGE 1 PHASE 6 */
	case Phase::SIX:
	game->ClearEntities(false);
	ge2 = game->acquireGenericEnemy2();
	ge2->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::SOUTH_ROT,
				EnemyConfig::GENERC_1_SPEED);

	starFP = game->acquireStarFP();
	ge2->setFiringPattern(starFP);
	
	game->SpawnEnemy(ge2);
	break;
	/* STAGE 1 PHASE 7 */
	case Phase::SEVEN:
	game->ClearEntities(false);
	ge2 = game->acquireGenericEnemy2();
	ge2->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::SOUTH_ROT,
				EnemyConfig::GENERC_1_SPEED);

	starFP = game->acquireStarFP();
	ge2->setFiringPattern(starFP);

	circularMP = game->acquireCircularMP();
	ge2->setMovementPattern(circularMP);
	
	game->SpawnEnemy(ge2);
	break;
	/* STAGE 1 PHASE 8 */
	case Phase::EIGHT:
	game->ClearEntities(false);
	ge2 = game->acquireGenericEnemy2();
	ge2->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::SOUTH_ROT,
				EnemyConfig::GENERC_1_SPEED);

	spinFP = game->acquireSpinFP();
	ge2->setFiringPattern(spinFP);
	
	game->SpawnEnemy(ge2);
	break;
	/* STAGE 1 PHASE 9 */
	case Phase::NINE:
	game->ClearEntities(false);
	ge2 = game->acquireGenericEnemy2();
	ge2->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::SOUTH_ROT,
				EnemyConfig::GENERC_1_SPEED);

	spinFP = game->acquireSpinFP();
	ge2->setFiringPattern(spinFP);

	circularMP = game->acquireCircularMP();
	ge2->setMovementPattern(circularMP);
	
	game->SpawnEnemy(ge2);
	break;
	/* STAGE 1 PHASE 10 */
	case Phase::TEN:
	game->ClearEntities(false);
	ge2 = game->acquireGenericEnemy2();
	ge2->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::SOUTH_ROT,
				EnemyConfig::GENERC_1_SPEED);

	spinFP = game->acquireSpinFP();
	spinFP->setBulletSpeed(150.0f);
	spinFP->setShootCooldown(0.25f);
	ge2->setFiringPattern(spinFP);
	
	game->SpawnEnemy(ge2);
	break;
	/* STAGE 1 PHASE 11 */
	case Phase::ELEVEN:
	game->ClearEntities(false);
	ge2 = game->acquireGenericEnemy2();
	ge2->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::SOUTH_ROT,
				EnemyConfig::GENERC_1_SPEED);

	spinFP = game->acquireSpinFP();
	ge2->setFiringPattern(spinFP);

	circularMP = game->acquireCircularMP();
	ge2->setMovementPattern(circularMP);
	
	game->SpawnEnemy(ge2);
	break;
	/* STAGE 1 PHASE 12 */
	case Phase::TWELVE:
	game->ClearEntities(false);
	ge2 = game->acquireGenericEnemy2();
	ge2->Init(Vector2{(float)game->GetGameX()+game->GetGameWidth()/2, 200}, 
				Gameplay::SOUTH_ROT,
				EnemyConfig::GENERC_1_SPEED);

	spinFP = game->acquireSpinFP();
	spinFP->setBulletSpeed(150.0f);
	spinFP->setShootCooldown(0.25f);
	ge2->setFiringPattern(spinFP);
	
	game->SpawnEnemy(ge2);
	break;
	/* STAGE 1 PHASE 13 */
	case Phase::THIRTEEN:
	game->ClearEntities(false);
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
