#pragma once

#include <raylib.h>
#include "../../../include/constants/mp_constants.h"
#include "../../../include/constants/gameplay_constants.h"
#include "../../game/manager/PoolObject.h"

class Enemy;
class Game;

/* *********************************** */
/* MOVEMEMENT PATTERN ABSTRACT CLASSES */
/* *********************************** */

class MovementPattern : public PoolObject
{
protected:
	Game* game;
	Enemy* owner;

	MPType type;
public:
    MovementPattern(Game* game);

	virtual void Init  ();
	virtual void Update(float deltaTime) = 0;
	virtual void Setup ();

	MPType getType();

	void setOwner(Enemy* owner);

	virtual ~MovementPattern() = default;
};


/* ********************************** */
/* MOVEMEMENT PATTERN DERIVED CLASSES */
/* ********************************** */

/* Linear */
class LinearMP : public MovementPattern {
public:
    LinearMP(Game* game);
	void Update(float deltaTime);
};

/* Circular */
class CircularMP : public MovementPattern {
protected:
	Gameplay::Dir centerOffsetDir;
	float rotation;
	float radiusX, radiusY;
	float centerX, centerY;
	int   clockwise;
	float rotateSpeed;
public:
    CircularMP(Game* game);
	virtual void Update(float deltaTime);
	void Init  () override;
	void Setup () override;

	void setRadius (float rad);
	void setRadiusX(float radX);
	void setRadiusY(float radY);

	void setClockwise       ();
	void setCounterClockwise();

	void setCenterOffsetDir(Gameplay::Dir offsetDir);
	void setRotateSpeed     (float spd);
};

/* Circular Arc */
class CircularArcMP : public CircularMP {
private:
	float deltaTheta;
	float desiredArcAngle;
public:
    CircularArcMP(Game* game);
	void Update(float deltaTime) override;
	void Init  () override;

	void setDesiredArcAngle(float degrees);
};

/* Sinusoidal Curve */
class SinusoidalCurveMP : public MovementPattern
{
private:
	float startX;
	float startY;
	float speedX;
	float amplitude;
	float frequency;
public:
    SinusoidalCurveMP(Game* game);

	void Update(float deltaTime);

	void Init () override;
	void Setup() override;

	void setSpeedX   (float spdx);
	void setAmplitude(float amp);
	void setFrequency(float amp);
};

/* Parabolic Curve */
class ParabolicCurveMP : public MovementPattern
{
private:
	float startX;
	float startY;
	float curvature;
	float speedX;
public:
    ParabolicCurveMP(Game* game);

	void Update(float deltaTime);

	void Init () override;
	void Setup() override;

	void setCurvature(float curv);
	void setSpeedX   (float spdx);

};

/* Left Right Loop */
class LeftRightLoopMP : public MovementPattern
{
public:
	LeftRightLoopMP(Game* game);
	void Update(float deltaTime);
};