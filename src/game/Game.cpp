#include <string>
#include <iomanip>
#include <sstream>

#include "Game.h"
#include "GameMode.h"
#include "../entity/bullet/Bullet.h"
#include "../entity/enemy/Enemy.h"
#include "../entity/_spawner/Spawner.h"
#include "../entity/_pattern/FiringPattern.h"
#include "../entity/_pattern/MovementPattern.h"
#include "../entity/player/Player.h"


#include "../utils/Utils.h"

#include "../../include/constants/graphics_constants.h"

Game::Game()
: gameDimensions((Rectangle){GAME_X, GAME_Y, GAME_WIDTH, GAME_HEIGHT}),
  /* Stage Phase */
  stage(Stage::ONE), phase(Phase::ONE),
  /* Game Mode*/
  gameMode(new DebugMode(this)), 
  /* managers */
  textureMgr(), poolMgr(this), backgroundMgr(this),
  /* game booleans */
  gameOver(false), paused(false), debug(false), 
  /* player stats */
  score(0), lives(Gameplay::INITIAL_LIVES), bombs(Gameplay::INITIAL_BOMBS), power(Gameplay::INITIAL_POWER),
  hitTimer(Gameplay::HIT_COOLDOWN), hitCooldown(Gameplay::HIT_COOLDOWN),
  /* player */
  player(this),
  /* stage phase helpers */
  counter(0), enemyCount(0), moveTimer(0), moveInterval(0)
{
}

void Game::Init()
{	
	stage = Stage::ONE;
	phase = Phase::ONE;

	gameOver = false;
	paused   = false;
	debug    = false;

	score = 0;
	lives = Gameplay::INITIAL_LIVES;
	bombs = Gameplay::INITIAL_BOMBS;
	power = Gameplay::INITIAL_POWER;

	hitTimer = Gameplay::HIT_COOLDOWN;

	player.Init();
	gameMode->Init();
}

void Game::HandleInput()
{
	float deltaTime = GetFrameTime();
	player.HandleInput(deltaTime);

	if(IsKeyPressed(KEY_ESCAPE)) { paused = !paused; }
	if(IsKeyPressed(KEY_F3))     { debug  = !debug;  }

	gameMode->HandleInput();
}

void Game::Update()
{
	if(!paused)
	{
		float deltaTime = GetFrameTime();
		backgroundMgr.Update(deltaTime);

		gameMode->Update(deltaTime);

		player.Update(deltaTime);

		for(auto& enemy : inUseEnemies)
		{
			enemy->Update(deltaTime);
		}

		for(auto& bullet : inUseBullets)
		{
			bullet->Update(deltaTime);
		}

		RemoveNotInUseEntities();
		CheckCollisions();
		UpdateTimers();
	}
}

void Game::CheckCollisions()
{
	// Enemy collisions with player
	for(auto& enemy : inUseEnemies)
	{
		if(enemy->checkCollision(&player))
		{
			//std::cout << "enemy hit player\n";
			handlePlayerHit();
			break;
		}
	}
	if(hitTimer >= hitCooldown)
	{
		for(auto& enemy : inUseEnemies)
		{
			if(enemy->checkCollision(&player))
			{
				//std::cout << "enemy hit player\n";
				handlePlayerHit();
				break;
			}
		}
	}
	else hitTimer += GetFrameTime();

	// Bullet collisions
	for(auto& bullet : inUseBullets)
	{
		if(bullet->getType() == BulletConfig::Type::PLAYER)
		{
			for(auto& enemy : inUseEnemies)
			{
				if(bullet->checkCollision(enemy))
				{
					//std::cout << "player bullet hit enemy\n";
					enemy->setHp(enemy->getHp()-power);
					//std::cout << enemy->getHp() << "\n";
				}
			}
		}
		else
		{
			if(bullet->checkCollision(&player))
			{
				//std::cout << "bullet hit player\n";
				handlePlayerHit();
				break;
			}
		}
	}
}

void Game::ClearEntities(bool bulletPoints)
{
	for(auto& enemy : inUseEnemies)
	{
		enemy->Clear();
	}

	for(auto& bullet : inUseBullets)
	{
		if(bullet->getType() != BulletConfig::Type::PLAYER)
		{
			bullet->Clear();
			if(bulletPoints) 
				score += BulletConfig::POINTS;
		}
	}

	RemoveNotInUseEntities();
}

void Game::RemoveNotInUseEntities()
{
	inUseEnemies.erase(std::remove_if(
					inUseEnemies.begin(), inUseEnemies.end(),
					[](Enemy* enemy) { 
						return !enemy->isInUse();
					}), inUseEnemies.end());

	inUseBullets.erase(std::remove_if(
    					inUseBullets.begin(), inUseBullets.end(),
   						[](Bullet* bullet) { 
       						return !bullet->isInUse();
    					}), inUseBullets.end());
}

void Game::UpdateTimers()
{
	float frameTime = GetFrameTime();
	if(gameTimer < Gameplay::MAX_GAME_TIMER) gameTimer += frameTime;
	if(hitTimer  < Gameplay::HIT_COOLDOWN)   hitTimer  += frameTime;
}

void Game::SpawnEnemy (Enemy*  enemy)  
{ 
	if(enemy != nullptr)
	{
		inUseEnemies.push_back(enemy); enemy->Spawn();
	} 
}
void Game::SpawnBullet(Bullet* bullet) 
{ 
	if(bullet != nullptr)
	{
		inUseBullets.push_back(bullet);
	}
}

void Game::Draw()
{
	ClearBackground(BLACK);

	backgroundMgr.Draw();

	player.Draw();

	for(auto& bullet : inUseBullets)
		bullet->Draw();

	for(auto& enemy : inUseEnemies)
		enemy->Draw();

	DrawUI();
}

void Game::DrawUI()
{
	DrawRectangle(0,0,GetScreenWidth(), GAME_Y,  BLACK);
	DrawRectangle(0,0,GAME_X, GetScreenHeight(), BLACK);
	DrawRectangle(0, GAME_X+GAME_WIDTH, GetScreenWidth(), GetScreenHeight(), BLACK);
	DrawRectangle(GAME_X+GAME_WIDTH,
	              GAME_Y,
				  GetScreenWidth(),
				  GAME_Y+GAME_HEIGHT, BLACK);
	DrawRectangleLines(GetGameX(), GetGameY(), GetGameWidth(), GetGameHeight(), WHITE);
	
	int height = GAME_UI_Y;

	std::string displayDebug = "debug: " + std::string(debug ? "true" : "false");
	DrawText(displayDebug.c_str(), GAME_UI_X, GAME_UI_Y, 20, WHITE); 
	if(debug)
	{
		DrawText(TextFormat("enemies: %04i", inUseEnemies.size()), GAME_UI_X + 150, GAME_UI_Y, 20, WHITE);
		DrawText(TextFormat("bullets: %07i", inUseBullets.size()), GAME_UI_X + 300, GAME_UI_Y, 20, WHITE);
	}
	height += 25;

	DrawText(formatTime(gameTimer).c_str(), GAME_UI_X, GAME_UI_Y+height, 30, WHITE); height += 35;

	DrawText(TextFormat("Score: %09i", score), GAME_UI_X, GAME_UI_Y+height, 40, WHITE);  height += 45;

	height += 30;

	DrawText(TextFormat("Lives: %02i", lives), GAME_UI_X, GAME_UI_Y+height, 30, WHITE); height += 35;
	DrawText(TextFormat("Bombs: %02i", bombs), GAME_UI_X, GAME_UI_Y+height, 30, WHITE); height += 35;
	DrawText(TextFormat("Power: %02i", power), GAME_UI_X, GAME_UI_Y+height, 30, WHITE); height += 35;
	
	height += 30;

	DrawText(TextFormat("Stage: %02i", static_cast<int>(stage)+1), GAME_UI_X, GAME_UI_Y+height, 30, WHITE); height += 35;
	DrawText(TextFormat("Phase: %02i", static_cast<int>(phase)+1), GAME_UI_X, GAME_UI_Y+height, 30, WHITE); height += 35;

	height += 30;

	DrawText("Controls:", GAME_UI_X, GAME_UI_Y+height, 30, WHITE); height += 35;
	DrawText("Up, Down, Left, Right: Move", GAME_UI_X, GAME_UI_Y+height, 20, WHITE); height += 25;
	DrawText("Left Shift: Focus", GAME_UI_X, GAME_UI_Y+height, 20, WHITE); height += 25;
	DrawText("W or Z: Shoot", GAME_UI_X, GAME_UI_Y+height, 20, WHITE); height += 25;
	DrawText("X: Bomb [NOT IMPLEMENTED]", GAME_UI_X, GAME_UI_Y+height, 20, WHITE); height += 25;
	DrawText("J: Previous phase", GAME_UI_X, GAME_UI_Y+height, 20, WHITE); height += 25;
	DrawText("K: Next phase", GAME_UI_X, GAME_UI_Y+height, 20, WHITE); height += 25;
	DrawText("R: Reload phase", GAME_UI_X, GAME_UI_Y+height, 20, WHITE); height += 25;
	DrawText("F3: Debug", GAME_UI_X, GAME_UI_Y+height, 20, WHITE); height += 25;
}

std::string Game::formatTime(float timer) 
{
    int seconds = static_cast<int>(timer);
    int mm = seconds / 60;
    int ss = seconds % 60;

    std::ostringstream timeStream;
    timeStream << std::setfill('0') << std::setw(2) << mm
               << ":" << std::setfill('0') << std::setw(2) << ss;
    return timeStream.str();
}

int Game::GetGameX     (){ return gameDimensions.x;      }
int Game::GetGameY     (){ return gameDimensions.y;      }
int Game::GetGameWidth (){ return gameDimensions.width;  }
int Game::GetGameHeight(){ return gameDimensions.height; }

Player* Game::getPlayer() { return &player; }

Stage Game::getStage() { return stage;   }
Phase Game::getPhase() { return phase;   }

void Game::setStage(Stage stage) { this->stage = stage; }
void Game::setPhase(Phase phase) { this->phase = phase; }


/* *** */
/* GET */
/* *** */

/* Bullets */
Bullet*        Game::acquireBullet       () { return poolMgr.acquireBullet(); }
/* Enemies */
GenericEnemy1* Game::acquireGenericEnemy1() { return poolMgr.acquireGenericEnemy1(); }
GenericEnemy2* Game::acquireGenericEnemy2() { return poolMgr.acquireGenericEnemy2(); }

/* Firing Patterns */
StraightFP* Game::acquireStraightFP() { return poolMgr.acquireStraightFP(); }
TargetedFP* Game::acquireTargetedFP() { return poolMgr.acquireTargetedFP(); }
StarFP*     Game::acquireStarFP    () { return poolMgr.acquireStarFP    (); }
SpinFP*     Game::acquireSpinFP    () { return poolMgr.acquireSpinFP    (); }

/* Movement Patterns */
LinearMP*        Game::acquireLinearMP       () { return poolMgr.acquireLinearMP       (); }
CircularMP*      Game::acquireCircularMP     () { return poolMgr.acquireCircularMP     (); }
CircularArcMP*   Game::acquireCircularArcMP  () { return poolMgr.acquireCircularArcMP  (); }
SinusoidalArcMP* Game::acquireSinusoidalArcMP() { return poolMgr.acquireSinusoidalArcMP(); }
ParabolicArcMP*  Game::acquireParabolicArcMP () { return poolMgr.acquireParabolicArcMP (); }
LeftRightLoopMP* Game::acquireLeftRightLoopMP() { return poolMgr.acquireLeftRightLoopMP(); }

/* ******* */
/* RELEASE */
/* ******* */

void Game::releaseBullet(Bullet*          bullet) { poolMgr.releaseInUseBullet(bullet); }
void Game::releaseEnemy (Enemy*           enemy ) { poolMgr.releaseInUseEnemy (enemy ); }
void Game::releaseFP    (FiringPattern*   fp    ) { poolMgr.releaseInUseFP    (fp    ); }
void Game::releaseMP    (MovementPattern* mp    ) { poolMgr.releaseInUseMP    (mp    ); }

Texture2D* Game::getTexture(TextureID id){ return textureMgr.getTexture(id); }

void Game::increaseScore(int points){score += points;}

void Game::handlePlayerHit()
{
	if(hitTimer >= hitCooldown)
	{
		lives--;
		hitTimer = 0;
	}
}

bool Game::isGameOver(){return gameOver;}
bool Game::isPaused  (){return paused;  }
bool Game::isDebug   (){return debug;   }

Game::~Game()
{
	delete gameMode;
}