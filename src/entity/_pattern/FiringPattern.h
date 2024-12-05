#pragma once

#include <raylib.h>
#include <array>

#include "../../../include/constants/fp_constants.h"

#include "../../entity/bullet/Bullet.h"
#include "../../entity/enemy/Enemy.h"
#include "../../entity/_spawner/Spawner.h"
#include "../../entity/player/Player.h"
#include "../../game/manager/PoolObject.h"


class Game;
class Enemy;
class Spawner;

/* ******************************* */
/* FIRING PATTERN ABSTRACT CLASSES */
/* ******************************* */

/* Firing Pattern */
class FiringPattern : public PoolObject
{
protected:
	Game* game;
	Enemy* owner;

	float bulletSpeed;
	float shootCooldown;

	FPType type;
public:
    FiringPattern(Game* game);

	virtual void Init  ();
	virtual void Update(float deltaTime) = 0;
	virtual void Draw  () = 0;
	virtual void Shoot () = 0;
	virtual void Setup () = 0;

	FPType getType();

	void setOwner(Enemy* owner);
	void setType(FPType type);

	void setShootCooldown(float shootCooldown);
	void setBulletSpeed  (float bulletSpeed);

	virtual void setAutoShoot() = 0;
	virtual void setManualShoot() = 0;

	virtual ~FiringPattern() = 0;
};

/* Single Spawner Firing Pattern */ 
class SingleSpawnerFP : public FiringPattern
{
protected:
	Spawner* spawner;
public:
	SingleSpawnerFP(Game* game);

	void Init  () override;
	void Draw  ();
	void Shoot ();

	void setAutoShoot() override;
	void setManualShoot() override;

	~SingleSpawnerFP();
};


/* Multi Spawner Firing Pattern */
class MultiSpawnerFP : public FiringPattern
{
protected:
	int spawnerCount;
	std::array<Spawner*, STAR_MAX_SPAWNER_COUNT> spawners;
public:
	MultiSpawnerFP(Game* game);

	void Init  () override;
	void Draw  ();
	void Shoot ();

	void setAutoShoot  () override;
	void setManualShoot() override;
	void setSpawnerCount(int newSpawnerCount);

	~MultiSpawnerFP();
};

/* ******************************* */
/* FIRING PATTERN DERIVED CLASSES */
/* ******************************* */

/* Targeted Firing Pattern */
class TargetedFP : public SingleSpawnerFP
{
public:
	TargetedFP(Game* game);
	void Update(float deltaTime);
	void Setup ();
};

/* Star Firing Pattern */
class StarFP : public MultiSpawnerFP
{
protected:
	float radius;
	float rotation;
public:
	StarFP(Game* game);

	void Init  () override;
	void Update(float deltaTime);
	void Setup ();

	void setRadius  (float rad);
	void setRotation(float rot);
};

/* Spin */
class SpinFP : public StarFP
{
private:
	float rotateSpeed;
	int   clockwise;
public:
	SpinFP(Game* game);

	void Init  () override;
	void Update(float deltaTime);

	void setRotateSpeed     (float rotateSpd);
	void setClockwise       ();
	void setCounterClockwise();
};