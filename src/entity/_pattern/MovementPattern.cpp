#include "MovementPattern.h"
#include "../_spawner/Spawner.h"
#include "../enemy/Enemy.h"
#include "../../game/Game.h"
#include "../../utils/Utils.h"

/* *********************************** */
/* MOVEMEMENT PATTERN ABSTRACT CLASSES */
/* *********************************** */

MovementPattern::MovementPattern(Game* game): PoolObject(), game(game), owner(nullptr) {}

void MovementPattern::Init ()
{
	owner = nullptr;
}

void MovementPattern::Setup(){}

MPType MovementPattern::getType(){ return type;  }

void MovementPattern::setOwner(Enemy* owner){ this->owner = owner; }

/* ********************************** */
/* MOVEMEMENT PATTERN DERIVED CLASSES */
/* ********************************** */

/* Linear */
LinearMP::LinearMP(Game *game) : MovementPattern(game)
{
	type = MPType::LINEAR; 
}

void LinearMP::Update(float deltaTime)
{
	owner->Move(deltaTime);
}

/* Circular */
CircularMP::CircularMP(Game *game) 
: MovementPattern(game), 
  centerOffsetDir(Gameplay::Dir::SOUTH),
  rotation(0.0f), radiusX(100.0f), radiusY(100.0f), centerX(0), centerY(0), clockwise(1), rotateSpeed(50.0f)
{
	type = MPType::CIRCULAR;
}

void CircularMP::Init()
{
	MovementPattern::Init();
	
	centerOffsetDir = Gameplay::Dir::SOUTH;
	rotation    = 0.0f;
	radiusX     = 100.0f;
	radiusY     = 100.0f;
	centerX     = 0;
	centerY     = 0;
	clockwise   = 1;
	rotateSpeed  = 50.0f;
}

void CircularMP::Setup()
{
	switch (centerOffsetDir)
	{
		case Gameplay::Dir::NORTH: 
			rotation = dirToRot(Gameplay::Dir::SOUTH);
			centerX  = owner->getX();
			centerY  = owner->getY() - radiusY;
			break;
		case Gameplay::Dir::EAST:
			rotation = dirToRot(Gameplay::Dir::WEST);
			centerX  = owner->getX() + radiusX;
			centerY  = owner->getY();
			break;
		case Gameplay::Dir::SOUTH:
			rotation = dirToRot(Gameplay::Dir::NORTH);
			centerX  = owner->getX();
			centerY  = owner->getY() + radiusY;
			break;
		case Gameplay::Dir::WEST:
			rotation = dirToRot(Gameplay::Dir::EAST);
			centerX  = owner->getX() - radiusX;
			centerY  = owner->getY();
			break;
		default: break;
	}
}

void CircularMP::Update(float deltaTime)
{
	rotation += rotateSpeed * deltaTime * clockwise;
	owner->setX(centerX + radiusX * (float)cos(degreesToRad(rotation)));
	owner->setY(centerY + radiusY * (float)sin(degreesToRad(rotation)));

	if(game->isDebug())
		DrawCircle(centerX, centerY, 10.0f, ORANGE);
}

void CircularMP::setRadius (float rad)  { radiusX = rad; radiusY = rad; }
void CircularMP::setRadiusX(float radx) { radiusX = radx; }
void CircularMP::setRadiusY(float rady) { radiusY = rady; }

void CircularMP::setClockwise       () { clockwise  = 1;  }
void CircularMP::setCounterClockwise() { clockwise  = -1; }

void CircularMP::setCenterOffsetDir(Gameplay::Dir offsetDir)
{
	centerOffsetDir = offsetDir;
}

void CircularMP::setRotateSpeed(float spd)
{
	rotateSpeed = spd;
}

/* Circular Arc */
CircularArcMP::CircularArcMP(Game *game) : CircularMP(game), deltaTheta(0), desiredArcAngle(90.0f)
{
	type = MPType::CIRCULAR_ARC;
}

void CircularArcMP::Update(float deltaTime)
{
	if (fabs(deltaTheta) < desiredArcAngle) 
	{
    	deltaTheta += owner->getSpeed()/180.0f * deltaTime;
		CircularMP::Update(deltaTime);
	}

	if(game->isDebug())
		DrawCircle(centerX, centerY, 10.0f, ORANGE);

}

void CircularArcMP::Init()
{
	CircularMP::Init();
	deltaTheta      = 0;
	desiredArcAngle = 90.0f;
}

void CircularArcMP::setDesiredArcAngle(float degrees)
{
	desiredArcAngle = (degrees < 0 ? degrees * -1 : degrees);

}

/* Sinusoidal Curve */
SinusoidalCurveMP::SinusoidalCurveMP(Game *game)
: MovementPattern(game), 
  startX(0), startY(0), speedX(50.0f), amplitude(100.0f), frequency(0.1f)
{
	type = MPType::SINUSOIDAL_CURVE;
}

void SinusoidalCurveMP::Update(float deltaTime)
{
	owner->addX(speedX * deltaTime);
    float xOffset = owner->getX() - startX;
    float newY = startY + amplitude * sin(0.1 * xOffset);
    owner->setY(newY);
}

void SinusoidalCurveMP::Init()
{
	startX    = 0;
	startY    = 0;
	speedX    = 50.0f;
	amplitude = 100.0f;
	frequency = 0.1f;
}

void SinusoidalCurveMP::Setup()
{
	startX = owner->getX();
	startY = owner->getY();
}

void SinusoidalCurveMP::setSpeedX   (float spdx) { speedX    = spdx;}
void SinusoidalCurveMP::setAmplitude(float amp)  { amplitude = amp; }
void SinusoidalCurveMP::setFrequency(float freq) { frequency = freq;}


/* Parabolic Curve */
ParabolicCurveMP::ParabolicCurveMP(Game *game) 
: MovementPattern(game), startX(0), startY(0), curvature(0.01f), speedX(50.0f)
{
	type = MPType::PARABOLIC_CURVE;
}

void ParabolicCurveMP::Update(float deltaTime)
{
	owner->addX(speedX * deltaTime);
	float xOffset = owner->getX() - startX;
    float newY = startY + curvature * xOffset * xOffset;
    owner->setY(newY);
}

void ParabolicCurveMP::Init()
{
	startX    = 0;
	startY    = 0;
	curvature = 0.01f;
	speedX    = 50.0f;
}

void ParabolicCurveMP::Setup()
{
	startX = owner->getX();
	startY = owner->getY();
}

void ParabolicCurveMP::setSpeedX   (float spdx) { speedX    = spdx;}
void ParabolicCurveMP::setCurvature(float curv) { curvature = curv;}


/* Left Right Loop */
LeftRightLoopMP::LeftRightLoopMP(Game* game)
: MovementPattern(game)
{
	type = MPType::LEFT_RIGHT_LOOP;
}

void LeftRightLoopMP::Update(float deltaTime)
{
	if(owner->getPosition().x < game->GetGameX() && owner->getRotation() == 180.0f) 
		owner->setRotation(0.0f);

	if(owner->getPosition().x > game->GetGameX() + game->GetGameWidth() && owner->getRotation() == 0.0f) 
		owner->setRotation(180.0f);

	owner->Move(deltaTime);
}