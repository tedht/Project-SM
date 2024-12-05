// Librairies
#include <raylib.h>
#include <cmath>
#include <iostream>

// Classes
#include "Bullet.h"
#include "../Entity.h"
#include "../../game/Game.h"
#include "../_pattern/MovementPattern.h"

// Constants
#include "../../../include/constants/graphics_constants.h"

void Bullet::InitType()
{
	switch (type)
	{
	case BulletConfig::Type::PLAYER:
		hitbox = BulletConfig::PLAYER_HITBOX; 
		frameX = static_cast<int>(BulletConfig::Type::PLAYER); 
		break;
	case BulletConfig::Type::TINY:
		hitbox = BulletConfig::TINY_HITBOX; 
		frameX = static_cast<int>(BulletConfig::Type::TINY); 
		break;
	case BulletConfig::Type::SMALL:
		hitbox = BulletConfig::SMALL_HITBOX; 
		frameX = static_cast<int>(BulletConfig::Type::SMALL); 
		break;
	case BulletConfig::Type::MEDIUM:
		hitbox = BulletConfig::MEDIUM_HITBOX;
		frameX = static_cast<int>(BulletConfig::Type::MEDIUM); 
		break;
	case BulletConfig::Type::LARGE:
		hitbox = BulletConfig::LARGE_HITBOX;
		frameX = static_cast<int>(BulletConfig::Type::LARGE); 
		break;
	default:
		break;
	}
}

Bullet::Bullet(Game *game)
: Entity(game), SpriteHandler(), PoolObject(),
  type(BulletConfig::Type::MEDIUM)
{
	setSprite(game->getTexture(TextureID::BULLET), 1, 5);
}

void Bullet::Init()
{
	type     = BulletConfig::Type::MEDIUM;
	InitType();
	position = Vector2{-500, -500};
	rotation = 0;
	speed    = BulletConfig::DEFAULT_BULLET_SPEED;
}

void Bullet::Init(BulletConfig::Type type, Vector2 pos, float rot, float spd)
{	
	this->type = type;
	InitType();
	position = pos;
	rotation = rot;
	speed    = spd;
}

void Bullet::Update(float deltaTime)
{
	Move(deltaTime);

	if(isOutOfBounds(50))
	{
		game->releaseBullet(this);
	}
}

void Bullet::Draw()
{
	SpriteHandler::Draw(position);

	// Hitbox
	if(game->isDebug())
	{
		DrawCircle(position.x, position.y, hitbox/2, GREEN);
	}
}

void Bullet::Clear()
{
	game->releaseBullet(this);
}

BulletConfig::Type Bullet::getType(){ return type; }

Bullet::~Bullet(){}
