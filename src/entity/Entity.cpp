#include <raylib.h>
#include <cmath>

#include "Entity.h"
#include "../utils/Utils.h"
#include "../game/Game.h"

Entity::Entity(Game *game) 
: game(game), position(Vector2{0, 0}), rotation(0), speed(0), hitbox(5.0f)
{
}

// Setters
Entity* Entity::setPosition(Vector2 pos) {position = pos; return this;}
Entity* Entity::setRotation(float   rot)
{
	if(rotation >= 360)	rot = fmod(rot, 360);
	rotation = rot;
	return this;
} 
Entity* Entity::setSpeed   (float   spd) { speed      = spd; return this; }
Entity* Entity::setHitbox  (float   htb) { hitbox     = htb; return this; }
Entity* Entity::setX       (float   x)   { position.x = x;   return this; }
Entity* Entity::setY       (float   y)   { position.y = y;   return this; }

// Getters
Vector2 Entity::getPosition(){return position;  }
float   Entity::getRotation(){return rotation;  }
float   Entity::getSpeed   (){return speed;     }
float   Entity::getHitbox  (){return hitbox;    }
float   Entity::getX       (){return position.x;}
float   Entity::getY       (){return position.y;}

// Other methods
void Entity::addRotation(int degrees)
{
	rotation = fmod(rotation+degrees,360);
}

void Entity::addX(float dist){ position.x += dist; }
void Entity::addY(float dist){ position.y += dist; }

void Entity::Move(float deltaTime)
{	
	float angleRad = rotation * PI / 180.0f;

	position.x += speed * deltaTime * cos(angleRad);
	position.y += speed * deltaTime * sin(angleRad);
}

bool Entity::checkCollision(Entity *other)
{
    float dist = distance(this->position, other->position);
	
	return dist <= this->hitbox/2 + other->hitbox/2;
}

bool Entity::isOutOfBounds()
{
	return isOutOfBounds(0);
}

bool Entity::isOutOfBounds(float margin)
{
	return (position.x < game->GetGameX() - margin || 
			position.x > game->GetGameX() + game->GetGameWidth () + margin || 
			position.y < game->GetGameY() - margin || 
			position.y > game->GetGameY() + game->GetGameHeight() + margin   );
}
