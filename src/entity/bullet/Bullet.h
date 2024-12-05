#pragma once

// Librairies
#include <raylib.h>

// Classes
#include "../Entity.h"
#include "../_spritehandler/SpriteHandler.h"
#include "../../game/manager/PoolObject.h"

// Constants
#include "../../../include/constants/bullet_constants.h"

class Game;
class MovementPattern;

class Bullet : public Entity, public SpriteHandler, public PoolObject
{
private:
	BulletConfig::Type type;
	bool    inUse;

	void InitType();
public:
    Bullet(Game *game);

	void Init();
	void Init(BulletConfig::Type type, Vector2 pos, float rot, float spd);
	void Update(float deltaTime);
    void Draw();
	void Clear();

	BulletConfig::Type getType();

	~Bullet();
};