#pragma once

#include <raylib.h>

class Game;

class Entity 
{
protected:
	Game *game;
    Vector2 position;
	float rotation;
	float speed;
	float hitbox;

public:
	// Constructor
    Entity(Game* game);

	// setters
	Entity* setPosition(Vector2 pos);
	Entity* setRotation(float   rot);
	Entity* setSpeed   (float   spd);
	Entity* setHitbox  (float   hb);
	Entity* setX       (float   x);
	Entity* setY       (float   y);

	// getters
	Vector2 getPosition();
	float   getRotation();
	float   getSpeed   ();
	float   getHitbox  ();
	float   getX       ();
	float   getY       ();

	// Other methods
	virtual void Update(float deltaTime) = 0;
	void Move(float deltaTime);

	void addRotation(int degrees);
	void addX(float dist);
	void addY(float dist);

	bool isOutOfBounds();
	bool isOutOfBounds(float margin);

	bool checkCollision(Entity* other);

	// Deconstructor
	virtual ~Entity() = default;
};