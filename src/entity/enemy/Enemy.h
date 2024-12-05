#pragma once

// Libraries
#include <vector>
#include <cmath>
#include <unordered_map>

// Constants
#include "../../../include/constants/enemy_constants.h"

// Classes
#include "../Entity.h"
#include "../_spritehandler/SpriteHandler.h"
#include "../_spawner/Spawner.h"
#include "../../game/manager/PoolObject.h"

class FiringPattern;
class MovementPattern;
class Game;

class Enemy : public Entity, public SpriteHandler, public PoolObject
{
protected:
	EnemyConfig::Type type;
	int  hp;
	int  points;

	FiringPattern* firingPattern;
	MovementPattern* movementPattern;

public:
    Enemy(Game *game);

	virtual void Init();
	virtual void Init(Vector2 pos, float rot, float spd);
	virtual void Update(float deltaTime);
	virtual void UpdateSprite();
    void Draw();
	void Shoot();
	void Clear();
	void Spawn();
	
	EnemyConfig::Type getType();
	int getHp    ();
	int getPoints();

	void setHp    (int hp);
	void setPoints(int points);

	void setFiringPattern  (FiringPattern*   fp);
	void setMovementPattern(MovementPattern* mp);

	virtual ~Enemy() = 0;
};

class GenericEnemy1 : public Enemy
{
public:
	GenericEnemy1(Game* game);
};

class GenericEnemy2 : public Enemy
{
public:
	GenericEnemy2(Game* game);
	void UpdateSprite();
};

