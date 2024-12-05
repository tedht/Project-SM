#pragma once

#include "./../Entity.h"
#include "../_spritehandler/SpriteHandler.h"
#include "../../../include/constants/spawner_constants.h"
#include "../../../include/constants/bullet_constants.h"

class Game;

class Spawner : public Entity, public SpriteHandler
{
protected:
	SpawnerConfig::Type type;
	BulletConfig::Type  bulletType;
	float               bulletSpeed;

	float shootTimer;
	float shootCooldown;
	bool  autoShoot;
public:
    // Constructor
    Spawner(Game *game);

	void Init();
	void Init(BulletConfig::Type bulletType, float bulletSpd, Vector2 pos, float rot, float cooldown);
	void Init(BulletConfig::Type bulletType, float bulletSpd, Vector2 pos, float rot, float spd, float cooldown);
	virtual void Update(float deltaTime);
	virtual void Shoot();
	void Draw();

	SpawnerConfig::Type getType();
	BulletConfig::Type  getBulletType();
	float               getBulletSpeed();

	void setManualShoot();
	void setAutoShoot  ();
	void setShootCoooldown(float shootCooldown);
	

	virtual ~Spawner() = 0; 
};


class StraightSpawner : public Spawner
{
public:
   	StraightSpawner(Game *game);
};

class TargetedSpawner : public Spawner
{
public:
   	TargetedSpawner(Game *game);
	void Shoot();
};

class RotatingSpawner : public Spawner
{
private:
	float rotateSpd;
public:
   	RotatingSpawner(Game *game);
	void Update(float deltaTime);
	void Init(float rotateSpd,
		      BulletConfig::Type bulletType, 
	          float              bulletSpd, 
		      Vector2 pos, 
		      float   rot, 
		      float   spd, 
		      float   cooldown);
};


