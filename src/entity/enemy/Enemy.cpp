// Libraries
#include <iostream>

// Classes
#include "Enemy.h"
#include "../_spawner/Spawner.h"
#include "../../utils/Utils.h"
#include "../../game/Game.h"
#include "../_pattern/FiringPattern.h"
#include "../_pattern/MovementPattern.h"

// Constants
#include "../../../include/constants/graphics_constants.h"

Enemy::Enemy(Game *game)
	: Entity(game), SpriteHandler(), PoolObject(),
	  hp(EnemyConfig::DEFAULT_HP),
	  points(EnemyConfig::DEFAULT_POINTS),
	  firingPattern(nullptr),
	  movementPattern(nullptr)
{
}

void Enemy::Init()
{
	position = Vector2{-500, -500};
	rotation = EnemyConfig::DEFAULT_ROTATION;
	speed    = EnemyConfig::DEFAULT_SPEED;
	hitbox   = EnemyConfig::DEFAULT_HITBOX;
	hp       = EnemyConfig::DEFAULT_HP;
	points   = EnemyConfig::DEFAULT_POINTS;
	
	firingPattern   = nullptr;
	movementPattern = nullptr;
}

void Enemy::Init(Vector2 pos, float rot, float spd)
{
	position = pos;
	rotation = rot;
	speed    = spd;
	hitbox   = EnemyConfig::DEFAULT_HITBOX;
	hp       = EnemyConfig::DEFAULT_HP;
	points   = EnemyConfig::DEFAULT_POINTS;

	hp = EnemyConfig::DEFAULT_HP;
}

void Enemy::Update(float deltaTime)
{
	if(hp <= 0) Clear();

	if(firingPattern != nullptr)
		firingPattern->Update(deltaTime);

	if(movementPattern != nullptr)
		movementPattern->Update(deltaTime);

	UpdateSprite();
}

void Enemy::UpdateSprite() { SpriteHandler::Update(); }

void Enemy::Draw()
{
	SpriteHandler::Draw(position);

	//Hitbox
	if(game->isDebug())
	{
		DrawCircle(position.x, position.y, hitbox/2, BLUE);
	}

	
	if(firingPattern != nullptr)
		firingPattern->Draw();
}

void Enemy::Shoot()
{
	firingPattern->Shoot();
}

void Enemy::Clear()
{
	if(firingPattern)
		game->releaseFP(firingPattern);

	if(movementPattern)
		game->releaseMP(movementPattern);
	
	game->releaseEnemy(this);
}

void Enemy::Spawn()
{
	if(firingPattern != nullptr)
		firingPattern->Setup();

	if(movementPattern != nullptr)
		movementPattern->Setup();
}

EnemyConfig::Type Enemy::getType  (){return type;  }
int               Enemy::getHp    (){return hp;    }
int               Enemy::getPoints(){return points;}

void Enemy::setHp    (int hp)     { this->hp     = hp;     }
void Enemy::setPoints(int points) { this->points = points; }

void Enemy::setFiringPattern(FiringPattern* fp)
{
	fp->setOwner(this);
	firingPattern = fp;
}

void Enemy::setMovementPattern(MovementPattern* mp)
{
	mp->setOwner(this);
	movementPattern = mp;
}

inline Enemy::~Enemy() {}

/* *********** */
/* ENEMY TYPES */
/* *********** */

GenericEnemy1::GenericEnemy1(Game *game) : Enemy(game)
{
	type = EnemyConfig::Type::GENERIC_1;
	setSprite(game->getTexture(TextureID::GE1), 2, 4);
}

GenericEnemy2::GenericEnemy2(Game *game) : Enemy(game)
{
	type = EnemyConfig::Type::GENERIC_2;
	setSprite(game->getTexture(TextureID::GE2), 1, 8);
}

void GenericEnemy2::UpdateSprite()
{
	framesCounter++;
	if (framesCounter >= (60/frameSpeed))
	{
		framesCounter = 0;
		frameX = randomInt(0, cols-1);
		if (frameX > maxFrameX) frameX = 0;
	}
}
