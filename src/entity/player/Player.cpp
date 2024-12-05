#include <raylib.h>
#include <iostream>
#include <cmath>

#include "Player.h"
#include "PlayerState.h"
#include "../Entity.h"
#include "../bullet/Bullet.h"
#include "../../game/Game.h"
#include "../../game/manager/PoolManager.h"
#include "../../../include/constants/gameplay_constants.h"
#include "../../../include/constants/graphics_constants.h"

Player::Player(Game *game)
: Entity(game), shootTimer(0)
{
	spriteSheet = game->getTexture(TextureID::PLAYER);

	stateHandlers[PSHIndex::MOVEMENT] = new MovementStateHandler(this);
	stateHandlers[PSHIndex::MOVEMENT]->setState(Idle::getInstance());

	stateHandlers[PSHIndex::FIRING] = new FiringStateHandler(this);
	stateHandlers[PSHIndex::FIRING]->setState(Standby::getInstance());
}


void Player::Init()
{
	position = Vector2{(float)(game->GetGameX() + game->GetGameWidth ()/2),
	                   (float)(game->GetGameY() + game->GetGameHeight()/2),};
	rotation = 0;
	speed    = PlayerConfig::DEFAULT_SPEED;
	hitbox   = PlayerConfig::HITBOX;
	shootTimer = 0;

	stateHandlers[PSHIndex::MOVEMENT]->setState(Idle::getInstance());
	stateHandlers[PSHIndex::FIRING]->setState(Standby::getInstance());
}

void Player::Update(float deltaTime) 
{		
	if(shootTimer < PlayerConfig::SHOOT_COOLDOWN)
		shootTimer += deltaTime;
	
	if (position.x < game->GetGameX())
		position.x = game->GetGameX();
	if (position.x > game->GetGameX() + game->GetGameWidth())
		position.x = game->GetGameX() + game->GetGameWidth();
	if (position.y < game->GetGameY())
		position.y = game->GetGameY();
	if (position.y > game->GetGameY() + game->GetGameHeight())
		position.y = game->GetGameY() + game->GetGameHeight();

	for(PlayerStateHandler* stateHandler : stateHandlers)
	{
		stateHandler->Update();
		stateHandler->HandleInput(this);
	}
}

void Player::Draw()
{
	for(PlayerStateHandler* stateHandler : stateHandlers)
		DrawTexturePro(*spriteSheet, 
		               stateHandler->getSrc(), 
					   stateHandler->getDest(position), 
					   (Vector2){0, 0}, 0, WHITE);

	if(IsKeyDown(KEY_LEFT_SHIFT))
		DrawCircle(position.x, position.y, hitbox/2, RED);
}

void Player::HandleInput(float deltaTime)
{
	if (IsKeyDown(KEY_RIGHT)){ rotation = Gameplay::EAST_ROT;  Move(deltaTime); }
	if (IsKeyDown(KEY_DOWN)) { rotation = Gameplay::SOUTH_ROT; Move(deltaTime); }
	if (IsKeyDown(KEY_LEFT)) { rotation = Gameplay::WEST_ROT;  Move(deltaTime); }
	if (IsKeyDown(KEY_UP))   { rotation = Gameplay::NORTH_ROT; Move(deltaTime); }

	if(IsKeyDown(KEY_W) || IsKeyDown(KEY_Z)) Shoot();
}

void Player::Shoot()
{
	if(shootTimer >= PlayerConfig::SHOOT_COOLDOWN)
	{
		shootTimer = 0;

		Bullet* bullet = game->acquireBullet();
		bullet->Init(BulletConfig::Type::PLAYER, 
					position, 
					BulletConfig::PLAYER_BULLET_ROTATION, 
					BulletConfig::PLAYER_BULLET_SPEED);
		game->SpawnBullet(bullet);
	}
}

