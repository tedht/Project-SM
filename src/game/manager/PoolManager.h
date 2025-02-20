#pragma once

#include <array>
#include <queue>
#include <iostream>

#include "../../entity/bullet/Bullet.h"
#include "../../entity/enemy/Enemy.h"
#include "../../entity/_spawner/Spawner.h"
#include "../../entity/_pattern/FiringPattern.h"
#include "../../entity/_pattern/MovementPattern.h"
#include "../../entity/player/Player.h"

class Game;

template <typename T, size_t poolSize = 10>
class Pool 
{
	static_assert(std::is_base_of<PoolObject, T>::value, "T must inherit from PoolObject");

private:
    std::array<T*, poolSize> pool;
    std::queue<size_t> usableInds;

    void Init(Game* game);
public:
    Pool(Game* game);

    T* acquireObject();
    void releaseInUseObject(T* ptr);

	~Pool();
};

class PoolManager
{
private:
	/* Entities */
	Pool<Bullet,        100000> bulletPool;
    Pool<GenericEnemy1, 100> GE1Pool;
    Pool<GenericEnemy2, 100> GE2Pool;

	/* Firing Patterns */
	Pool<StraightFP, 100> straightFPPool;
	Pool<TargetedFP, 100> targetedFPPool;
	Pool<StarFP,     100> starFPPool;
	Pool<SpinFP,     100> spinFPPool;

	/* Movement Patterns */
	Pool<LinearMP,        100> linearMPPool;
	Pool<CircularMP,      100> circularMPPool;
	Pool<CircularArcMP,   100> circularArcMPPool;
	Pool<SinusoidalArcMP, 100> sinusoidalArcMPPool;
	Pool<ParabolicArcMP,  100> parabolicArcMPPool;
	Pool<LeftRightLoopMP, 100> leftRightLoopMPPool;

public:
	PoolManager(Game* game);
	
	/* *** */
	/* GET */
	/* *** */

	/* Entities */
	Bullet*        acquireBullet       ();
	GenericEnemy1* acquireGenericEnemy1();
	GenericEnemy2* acquireGenericEnemy2();

	/* Firing Patterns */
	StraightFP* acquireStraightFP   ();
	TargetedFP* acquireTargetedFP   ();
	StarFP*     acquireStarFP       ();
	SpinFP*     acquireSpinFP       ();

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

	/* Entities */
	void releaseInUseBullet (Bullet* bullet);
	void releaseInUseEnemy  (Enemy*  enemy);

	/* Firing Patterns */	
	void releaseInUseFP(FiringPattern* fp);

	/* Movement Patterns */
	void releaseInUseMP(MovementPattern* fp);

	void releaseInUseObj(PoolObject* obj);

	~PoolManager();
};
