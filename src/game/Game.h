#pragma once

// Libraries
#include <raylib.h>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <unordered_map>

// Classes
#include "manager/PoolManager.h"
#include "manager/TextureManager.h"
#include "manager/BackgroundManager.h"

#include "../entity/player/Player.h"

// Constants
#include "../../include/constants/gameplay_constants.h"
#include "../../include/constants/enemy_constants.h"
#include "../../include/constants/bullet_constants.h"
#include "../../include/constants/spawner_constants.h"
#include "../../include/constants/fp_constants.h"
#include "../../include/constants/mp_constants.h"

/* ******************** */
/* Forward Declarations */
/* ******************** */

/* Game Mode */
class GameMode;

/* Entities */
class Bullet;
class Enemy;
class Spawner;

/* Firing Patterns */
class FiringPattern;
class StarFP;

/* Movement Patterns */
class MovementPattern;
class CircularM;

/* **** */
/* Game */
/* **** */
class Game 
{
private:
	Rectangle gameDimensions;

	Stage stage;
	Phase phase;

	GameMode* gameMode;

	TextureManager    textureMgr;
	PoolManager       poolMgr;
	BackgroundManager backgroundMgr;

	bool gameOver;
	bool paused;
	bool debug;

	int score;
	int lives;
	int bombs;
	int power;

	float gameTimer;
	float hitTimer;
	float hitCooldown;

	/* Player */
	Player player;

	/* InUse entities */

	std::vector<Enemy*>  inUseEnemies;
	std::vector<Bullet*> inUseBullets;

	// Stage/Phase Helpers
	int counter;
	int enemyCount;
	float countTimer;
	float countInterval;
	float moveTimer;
	float moveInterval;

public:
	Game();

	void Init       ();
	void Update     ();
	void HandleInput();

	void Draw  ();
	void DrawUI();

	void CheckCollisions();
	void ClearEntities(bool bulletPoints);
	void RemoveNotInUseEntities();
	void UpdateTimers();

	void SpawnEnemy (Enemy*  enemy);
	void SpawnBullet(Bullet* bullet);

	int GetGameX     ();
	int GetGameY     ();
	int GetGameWidth ();
	int GetGameHeight();

	Player* getPlayer();

	Stage getStage();
	Phase getPhase();
	void setStage(Stage stage);
	void setPhase(Phase phase);

	/* *** */
	/* GET */
	/* *** */

	/* Entities */
	Bullet*        acquireBullet       ();
	GenericEnemy1* acquireGenericEnemy1();
	GenericEnemy2* acquireGenericEnemy2();

	/* Firing Patterns */
	StraightFP* acquireStraightFP();
	TargetedFP* acquireTargetedFP();
	StarFP*     acquireStarFP    ();
	SpinFP*     acquireSpinFP    ();

	/* Movement Patterns */	
	LinearMP*        acquireLinearMP       ();
	CircularMP*      acquireCircularMP     ();	
	CircularArcMP*   acquireCircularArcMP  ();	
	SinusoidalArcMP* acquireSinusoidalArcMP();
	ParabolicArcMP*  acquireParabolicArcMP ();
	LeftRightLoopMP* acquireLeftRightLoopMP();

	/* ******* */
	/* RELEASE */
	/* ******* */

	void releaseBullet(Bullet*          bullet);
	void releaseEnemy (Enemy*           enemy );
	void releaseFP    (FiringPattern*   fp    );
	void releaseMP    (MovementPattern* mp    );

	Texture* getTexture(TextureID id);

	void increaseScore(int points);
	void handlePlayerHit();
	std::string formatTime(float timer);

	bool isGameOver();
	bool isPaused();
	bool isDebug();

	~Game();
};