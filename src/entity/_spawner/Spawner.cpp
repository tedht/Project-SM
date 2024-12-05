// Librairies
#include <iostream>
#include <cmath>

// classes
#include "Spawner.h"
#include "../../game/Game.h"
#include "../../game/manager/PoolManager.h"
#include "../player/Player.h"
#include "../../utils/Utils.h"
#include "../bullet/Bullet.h"

// Constants
#include "../../../include/constants/graphics_constants.h"

/* SPAWNER SUPER CLASS */

Spawner::Spawner(Game *game)
	: Entity(game), SpriteHandler(),
	  bulletType(BulletConfig::Type::MEDIUM),
	  bulletSpeed(0.0f),
	  shootTimer(0),
	  shootCooldown(0.0f),
	  autoShoot(true)
{
	setSprite(game->getTexture(TextureID::SPAWNER), 1, 7);
}

void Spawner::Init()
{
	position = Vector2{-500, -500};
	rotation = SpawnerConfig::DEFAULT_ROTATION;
	speed    = SpawnerConfig::DEFAULT_SPEED;
	hitbox   = SpawnerConfig::DEFAULT_HITBOX;
	frameX   = static_cast<int>(type); 
	
	shootTimer    = 0;
	shootCooldown = SpawnerConfig::DEFAULT_COOLDOWN;

	autoShoot = true;
}

void Spawner::Init(BulletConfig::Type bulletType, float bulletSpd, Vector2 pos, float rot, float cooldown)
{
	Init(bulletType, bulletSpd, pos, rot, 0.0f, cooldown);
}

void Spawner::Init(BulletConfig::Type bulletType, float bulletSpd, Vector2 pos, float rot, float spd, float cooldown)
{
	this->bulletType = bulletType;
	bulletSpeed      = bulletSpd;

	position      = pos;
	rotation      = rot;
	speed         = spd;
	shootCooldown = cooldown;
}

void Spawner::Update(float deltaTime)
{
	if(shootTimer < shootCooldown)
		shootTimer += deltaTime;

	if(autoShoot) Shoot();
}

void Spawner::Draw()
{
	DrawTexturePro(*texture, 
					getSrc(),
					getDest(position),
					(Vector2){frameWidth*SIZE_MULTIPLIER/2, frameHeight*SIZE_MULTIPLIER/2}, 
					rotation-90, 
					WHITE);

	DrawCircle(position.x, position.y, hitbox/2, WHITE);
}

void Spawner::Shoot()
{
	if(shootTimer >= shootCooldown)
	{
		shootTimer = 0;

		Bullet* bullet = game->acquireBullet();
		bullet->Init(bulletType, position, rotation, bulletSpeed);
		game->SpawnBullet(bullet);
	} 
}

SpawnerConfig::Type Spawner::getType(){return type;}

BulletConfig::Type Spawner::getBulletType (){return bulletType;}
float              Spawner::getBulletSpeed(){return bulletSpeed;}

void Spawner::setManualShoot(){autoShoot = false;}
void Spawner::setAutoShoot  (){autoShoot = true; }

void Spawner::setShootCoooldown(float shootCooldown){this->shootCooldown = shootCooldown;}

inline Spawner::~Spawner() {}

/* SPAWNER DERIVED CLASSES */

// Straight Spawner
StraightSpawner::StraightSpawner(Game *game) : Spawner(game)
{
	type = SpawnerConfig::Type::STRAIGHT;
}

// Targeted Spawner
TargetedSpawner::TargetedSpawner(Game *game) : Spawner(game)
{
	type = SpawnerConfig::Type::TARGETED;
}

void TargetedSpawner::Shoot()
{
	if(shootTimer >= shootCooldown)
	{
		shootTimer = 0;

		rotation = calculateAngle(position, game->getPlayer()->getPosition());

		Bullet* bullet = game->acquireBullet();
		bullet->Init(bulletType, position, rotation, bulletSpeed);
		game->SpawnBullet(bullet);
	} 
}

// Rotating Spawner 
RotatingSpawner::RotatingSpawner(Game *game) : Spawner(game)
{
	type = SpawnerConfig::Type::ROTATING;
}

void RotatingSpawner::Update(float deltaTime)
{
	if(shootTimer < shootCooldown)
		shootTimer += deltaTime;

	rotation = fmod(rotation + rotateSpd, 360);
}

void RotatingSpawner::Init(float rotateSpd,
							BulletConfig::Type bulletType, 
							float              bulletSpd, 
							Vector2 pos, 
							float   rot, 
							float   spd, 
							float   cooldown)
{
	this->rotateSpd = rotateSpd;
	Spawner::Init(bulletType, bulletSpd, pos, rot, spd, cooldown);
}
