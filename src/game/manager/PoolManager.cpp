
#include <type_traits>

#include "PoolManager.h"
#include "../Game.h"

#include "../../../include/constants/enemy_constants.h"
#include "../../../include/constants/bullet_constants.h"
#include "../../../include/constants/fp_constants.h"
#include "../../../include/constants/mp_constants.h"

/* Pool */
template <typename T, size_t poolSize>
Pool<T, poolSize>::Pool(Game* game)
{
	Init(game);
}

template <typename T, size_t poolSize>
inline void Pool<T, poolSize>::Init(Game* game)
{
	for (size_t i = 0; i < poolSize; ++i) 
	{
		pool[i] = new T(game);
		usableInds.push(i);
	}
}

template <typename T, size_t poolSize>
T* Pool<T, poolSize>::acquireObject()
{
	if (!usableInds.empty()) 
	{
		size_t i = usableInds.front();
		usableInds.pop();
		pool[i]->setInUse(true);
		
		return pool[i];
	}

	std::cerr << "Warning: No available objects in the pool." << std::endl;
	return nullptr;
}

template <typename T, size_t poolSize>
void Pool<T, poolSize>::releaseInUseObject(T* obj)
{
	if (obj) 
	{
		obj->Init();
		obj->setInUse(false);
		size_t i = obj - pool[0];
		usableInds.push(i);
	}
}

template <typename T, size_t poolSize>
Pool<T, poolSize>::~Pool()
{
	for(size_t i = 0; i < poolSize; i++) delete pool[i];
}

PoolManager::PoolManager(Game* game) :
/* Bullets*/
bulletPool(game), 
/* Enemies */
GE1Pool(game), GE2Pool(game),
/* Firing Patterns*/
straightFPPool(game), targetedFPPool(game), 
starFPPool    (game), spinFPPool    (game),
/* Movement Patterns*/
linearMPPool      (game), circularMPPool     (game), 
circularArcMPPool (game), sinusoidalArcMPPool(game), 
parabolicArcMPPool(game), leftRightLoopMPPool(game)
{
}

/* *** */
/* GET */
/* *** */

/* Bullets */
Bullet*        PoolManager::acquireBullet       () { return bulletPool    .acquireObject(); }
/* Enemies */
GenericEnemy1* PoolManager::acquireGenericEnemy1() { return GE1Pool       .acquireObject(); }
GenericEnemy2* PoolManager::acquireGenericEnemy2() { return GE2Pool       .acquireObject(); }

/* Firing Patterns */
StraightFP* PoolManager::acquireStraightFP() { return straightFPPool.acquireObject(); }
TargetedFP* PoolManager::acquireTargetedFP() { return targetedFPPool.acquireObject(); }
StarFP*     PoolManager::acquireStarFP    () { return starFPPool    .acquireObject(); }
SpinFP*     PoolManager::acquireSpinFP    () { return spinFPPool    .acquireObject(); }

/* Movement Patterns */
LinearMP*        PoolManager::acquireLinearMP       () { return linearMPPool       .acquireObject(); }
CircularMP*      PoolManager::acquireCircularMP     () { return circularMPPool     .acquireObject(); }
CircularArcMP*   PoolManager::acquireCircularArcMP  () { return circularArcMPPool  .acquireObject(); }
SinusoidalArcMP* PoolManager::acquireSinusoidalArcMP() { return sinusoidalArcMPPool.acquireObject(); }
ParabolicArcMP*  PoolManager::acquireParabolicArcMP () { return parabolicArcMPPool .acquireObject(); }
LeftRightLoopMP* PoolManager::acquireLeftRightLoopMP() { return leftRightLoopMPPool.acquireObject(); }

/* ******* */
/* RELEASE */
/* ******* */

/* Bullets */
void PoolManager::releaseInUseBullet(Bullet* bullet){ bulletPool.releaseInUseObject(bullet); }
/* Enemies */
void PoolManager::releaseInUseEnemy (Enemy*  enemy)
{
	switch (enemy->getType())
	{
	case EnemyConfig::Type::GENERIC_1:
		GE1Pool.releaseInUseObject(static_cast<GenericEnemy1*>(enemy)); break;
	case EnemyConfig::Type::GENERIC_2:
		GE2Pool.releaseInUseObject(static_cast<GenericEnemy2*>(enemy)); break;
	default:
		break;
	}
}

/* Firing Patterns */
void PoolManager::releaseInUseFP(FiringPattern *fp)
{
	switch (fp->getType())
	{
	case FPType::STRAIGHT:
		straightFPPool.releaseInUseObject(static_cast<StraightFP*>(fp)); break;
	case FPType::TARGETED:
		targetedFPPool.releaseInUseObject(static_cast<TargetedFP*>(fp)); break;
	case FPType::STAR:
		starFPPool    .releaseInUseObject(static_cast<StarFP*>    (fp)); break;
	case FPType::SPIN:
		spinFPPool    .releaseInUseObject(static_cast<SpinFP*>    (fp)); break;
	default:
		break;
	}
}

/* Movement Patterns */
void PoolManager::releaseInUseMP(MovementPattern *mp)
{
	switch (mp->getType())
	{
	case MPType::LINEAR:
		linearMPPool       .releaseInUseObject(static_cast<LinearMP*>       (mp)); break;
	case MPType::CIRCULAR:
		circularMPPool     .releaseInUseObject(static_cast<CircularMP*>     (mp)); break;
	case MPType::CIRCULAR_ARC:
		circularArcMPPool  .releaseInUseObject(static_cast<CircularArcMP*>  (mp)); break;
	case MPType::SINUSOIDAL_ARC:
		sinusoidalArcMPPool.releaseInUseObject(static_cast<SinusoidalArcMP*>(mp)); break;
	case MPType::PARABOLIC_ARC:
		parabolicArcMPPool .releaseInUseObject(static_cast<ParabolicArcMP*> (mp)); break;
	case MPType::LEFT_RIGHT_LOOP:
		leftRightLoopMPPool.releaseInUseObject(static_cast<LeftRightLoopMP*>(mp)); break;
	default:
		break;
	}
}

void PoolManager::releaseInUseObj(PoolObject *obj)
{
	
}

PoolManager::~PoolManager()
{
}
