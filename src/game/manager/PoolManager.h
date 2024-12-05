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

constexpr int BULLET_COUNT = 100000;
constexpr int GE1_COUNT    = 100;
constexpr int GE2_COUNT    = 100;

constexpr int STAR_FP_COUNT     = 100;
constexpr int SPIN_FP_COUNT     = 100;
constexpr int TARGETED_FP_COUNT = 100;

constexpr int LINEAR_MP_COUNT   = 100;
constexpr int CIRCULAR_MP_COUNT = 100;

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
	Pool<Bullet,        BULLET_COUNT> bulletPool;
    Pool<GenericEnemy1, GE1_COUNT   > GE1Pool;
    Pool<GenericEnemy2, GE2_COUNT   > GE2Pool;

	/* Firing Patterns */
	Pool<StarFP,     STAR_FP_COUNT    >     starFPPool;
	Pool<SpinFP,     SPIN_FP_COUNT    >     spinFPPool;
	Pool<TargetedFP, TARGETED_FP_COUNT> targetedFPPool;

	/* Movement Patterns */
	Pool<LinearMP,   LINEAR_MP_COUNT  >   linearMPPool;
	Pool<CircularMP, CIRCULAR_MP_COUNT> circularMPPool;

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
	TargetedFP*    acquireTargetedFP   ();
	StarFP*        acquireStarFP       ();
	SpinFP*        acquireSpinFP       ();

	/* Movement Patterns */	
	LinearMP*      acquireLinearMP     ();
	CircularMP*    acquireCircularMP   ();	


	/* ******* */
	/* RELEASE */
	/* ******* */

	/* Entities */
	void releaseInUseBullet (Bullet* bullet);
	void releaseInUseEnemy  (Enemy*  enemy);
	//void releaseInUseGenericEnemy1(GenericEnemy1* ent);
	//void releaseInUseGenericEnemy2(GenericEnemy2* ent);

	/* Firing Patterns */	
	void releaseInUseFP(FiringPattern* fp);
	//void releaseInUseStarFP    (StarFP*     fp);
	//void releaseInUseTargetedFP(TargetedFP* fp);

	/* Movement Patterns */
	void releaseInUseMP(MovementPattern* fp);
	//void releaseInUseLinearMP  (LinearMP*   mp);
	//void releaseInUseCircularMP(CircularMP* mp);

	~PoolManager();
};
