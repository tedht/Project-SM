#include "FiringPattern.h"
#include "../_spawner/Spawner.h"
#include "../enemy/Enemy.h"
#include "../../game/Game.h"
#include "../../utils/Utils.h"

/* ******************************* */
/* FIRING PATTERN ABSTRACT CLASSES */
/* ******************************* */

/* Firing Pattern */
FiringPattern::FiringPattern(Game *game)
: PoolObject(), game(game), 
  bulletSpeed(BulletConfig::DEFAULT_BULLET_SPEED), 
  shootCooldown(SpawnerConfig::DEFAULT_COOLDOWN)
{
}

void FiringPattern::Init()
{
	shootCooldown = SpawnerConfig::DEFAULT_COOLDOWN;
	bulletSpeed   = BulletConfig::DEFAULT_BULLET_SPEED;
}
FPType FiringPattern::getType (){ return type; }

void FiringPattern::setOwner(Enemy* owner) { this->owner = owner; }
void FiringPattern::setType (FPType type)  { this->type  = type;  }

void FiringPattern::setShootCooldown(float shootCooldown) { this->shootCooldown = shootCooldown; }
void FiringPattern::setBulletSpeed  (float bulletSpeed)   { this->bulletSpeed = bulletSpeed; }

FiringPattern::~FiringPattern() {}

/* Single Spawner Firing Pattern */
SingleSpawnerFP::SingleSpawnerFP(Game *game) 
: FiringPattern(game) {}

void SingleSpawnerFP::Init()
{
	FiringPattern::Init();
	spawner->Init();
}
void SingleSpawnerFP::Draw (){ if(game->isDebug()) spawner->Draw(); }
void SingleSpawnerFP::Shoot(){ spawner->Shoot();                    }

void SingleSpawnerFP::setAutoShoot  (){ spawner->setAutoShoot  (); }
void SingleSpawnerFP::setManualShoot(){ spawner->setManualShoot(); }

SingleSpawnerFP::~SingleSpawnerFP() {delete spawner;}

/* Multi Spawner Firing Pattern */
MultiSpawnerFP::MultiSpawnerFP(Game *game)
: FiringPattern(game), spawnerCount(STAR_MAX_SPAWNER_COUNT) {}

void MultiSpawnerFP::Init()
{
	FiringPattern::Init();
	for(int i = 0;i < spawnerCount; i++) spawners[i]->Init();
}

void MultiSpawnerFP::Draw()
{
	if(game->isDebug())
	for(int i = 0; i < spawnerCount; i++) spawners[i]->Draw();
}

void MultiSpawnerFP::Shoot()
{
	for(int i = 0; i < spawnerCount; i++) spawners[i]->Shoot();
}

void MultiSpawnerFP::setAutoShoot()
{
	for(int i = 0; i < spawnerCount; i++) spawners[i]->setAutoShoot();

}

void MultiSpawnerFP::setManualShoot()
{
	for(int i = 0; i < spawnerCount; i++) spawners[i]->setManualShoot();

}

void MultiSpawnerFP::setSpawnerCount(int newSpawnerCount)
{
	if(newSpawnerCount > STAR_MAX_SPAWNER_COUNT) newSpawnerCount = STAR_MAX_SPAWNER_COUNT;
	if(newSpawnerCount < 0)                      newSpawnerCount = 0;
	this->spawnerCount = newSpawnerCount;


}

MultiSpawnerFP::~MultiSpawnerFP(){ for(auto* spawner : spawners) delete spawner; }

/* FIRING PATTERN DERIVED CLASSES*/

// Straight
StraightFP::StraightFP(Game *game) : SingleSpawnerFP(game)
{
	type = FPType::STRAIGHT;
	spawner = new StraightSpawner(game);
}

void StraightFP::Update(float deltaTime)
{
	spawner->setPosition(owner->getPosition());
	spawner->setRotation(owner->getRotation());
	spawner->Update(deltaTime);
}

void StraightFP::Setup()
{
	Vector2 spawnerPos = owner->getPosition();

	spawner->Init(BulletConfig::Type::MEDIUM,
				  bulletSpeed,
				  spawnerPos, 
				  owner->getRotation(),  
				  shootCooldown);
}

// TARGETED
TargetedFP::TargetedFP(Game* game) : SingleSpawnerFP(game)
{
	type = FPType::TARGETED;
	spawner = new TargetedSpawner(game);
}

void TargetedFP::Update(float deltaTime)
{
	spawner->setPosition(owner->getPosition());
	spawner->Update(deltaTime);
}

void TargetedFP::Setup()
{
	Vector2 spawnerPos = owner->getPosition();

	spawner->Init(BulletConfig::Type::MEDIUM,
				  bulletSpeed,
				  spawnerPos, 
				  owner->getRotation(),  
				  shootCooldown);
}



// STAR
StarFP::StarFP(Game *game) : MultiSpawnerFP(game), radius(20.0f), rotation(0)
{
	type = FPType::STAR;
	for(int i = 0;i < spawnerCount; i++) spawners[i] = new StraightSpawner(game);
}

void StarFP::Init()
{
	MultiSpawnerFP::Init();
	radius   = 20.0f;
	rotation = 0;
}

void StarFP::Update(float deltaTime)
{
	float rotation = 0;
	float angleRad;
	Vector2 spawnerPos;

	for(int i = 0; i < spawnerCount; i++)
	{
		angleRad = rotation * PI / 180.0f;
		spawnerPos.x = owner->getX() + radius * cos(angleRad);
		spawnerPos.y = owner->getY() + radius * sin(angleRad);
		
		spawners[i]->setPosition(spawnerPos);
		spawners[i]->Update(deltaTime);
			
		rotation += 360/spawnerCount;
	}
}

void StarFP::Setup()
{
	float   spawnerRot = rotation;
	Vector2 spawnerPos;

	for(int i = 0; i < spawnerCount; i++)
	{
		spawnerPos.x = owner->getX() + radius * cos(degreesToRad(spawnerRot));
		spawnerPos.y = owner->getY() + radius * sin(degreesToRad(spawnerRot));
		
		spawners[i]->Init(BulletConfig::Type::MEDIUM,
						bulletSpeed,
						spawnerPos, 
						spawnerRot, 
						2.0f, 
						shootCooldown);
		
		spawnerRot += 360/spawnerCount;
	}
}

void StarFP::setRadius  (float rad) { radius   = rad;}
void StarFP::setRotation(float rot) { rotation = rot;}

/* Spin */

SpinFP::SpinFP(Game *game) : StarFP(game), rotateSpeed(50.0f), clockwise(1)
{
	type = FPType::SPIN;
}

void SpinFP::Init()
{
	StarFP::Init();
	rotateSpeed = 50.0f;
	clockwise   = 1;
}

void SpinFP::Update(float deltaTime)
{
	rotation = fmod(rotation + rotateSpeed * deltaTime * clockwise, 360);
	float spawnerRot = rotation; 
	Vector2 spawnerPos;           

	for(int i = 0; i < spawnerCount; i++)
	{		
		spawnerPos.x = owner->getX() + radius * cos(degreesToRad(spawnerRot));
		spawnerPos.y = owner->getY() + radius * sin(degreesToRad(spawnerRot));

		spawners[i]->setPosition(spawnerPos);
		spawners[i]->setRotation(spawnerRot);
		spawners[i]->Update(deltaTime);
			
		spawnerRot += 360/spawnerCount;
	}
}

void SpinFP::setRotateSpeed(float rotateSpd) { rotateSpeed = rotateSpd; }

void SpinFP::setClockwise       () { clockwise = 1;  }
void SpinFP::setCounterClockwise() { clockwise = -1; }
