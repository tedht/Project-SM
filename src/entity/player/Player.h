#pragma once

#include "../../../include/constants/player_constants.h"
#include "./../Entity.h"

// Player State Handler Index
enum PSHIndex {
	MOVEMENT = 0,
	FIRING = 1
};

class Game;
class PlayerStateHandler;

class Player : public Entity
{
private:
	float shootTimer;

	PlayerStateHandler* stateHandlers[2];
	Texture2D* spriteSheet;
public:
    Player(Game *game);

	void Init();

	void HandleInput(float deltaTime);
	void Shoot();
	void Update(float deltaTime);
    void Draw();

	~Player() = default;
};
