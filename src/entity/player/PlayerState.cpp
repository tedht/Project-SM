#include <raylib.h>
#include <iostream>

#include "Player.h"
#include "PlayerState.h"

#include "../../../include/constants/graphics_constants.h"
#include "../../../include/constants/player_constants.h"

/* ********************* */
/* PLAYER STATE HANDLERS */
/* ********************* */

PlayerStateHandler::PlayerStateHandler(Player *player)
: player(player),
frameSpeed(DEFAULT_FRAME_SPEED), 

rows(PlayerConfig::SPRITESHEET_ROWS),  cols(PlayerConfig::SPRITESHEET_COLS),
frameWidth(PlayerConfig::FRAME_WIDTH), frameHeight(PlayerConfig::FRAME_HEIGHT), 

frameX(0), frameY(0), maxFrameX(cols-1), maxFrameY(rows-1), framesCounter(0),

currentState(&Idle::getInstance())
{
}

void PlayerStateHandler::Init()
{
	frameX = 0;
    framesCounter = 0;
	frameSpeed = DEFAULT_FRAME_SPEED;
}

void PlayerStateHandler::HandleInput(Player* player)
{
	currentState->HandleInput(this);
}

void PlayerStateHandler::Update()
{
	framesCounter++;
	if (framesCounter >= (60/frameSpeed))
	{
		framesCounter = 0;
		frameX++;
		if (frameX > maxFrameX) frameX = 0;
	}
}

void PlayerStateHandler::setState(PlayerState &newState)
{
	if (currentState != nullptr) 
		currentState->exit(this, player);

	currentState = &newState;

	if (currentState != nullptr) 
		currentState->enter(this, player);
}

void PlayerStateHandler::setFrameY    (int frameY)    {this->frameY     = frameY;    }
void PlayerStateHandler::setFrameSpeed(int frameSpeed){this->frameSpeed = frameSpeed;}

PlayerState* PlayerStateHandler::getState(){return currentState;}

std::string PlayerStateHandler::getName(){return currentState->getName();}

MovementStateHandler::MovementStateHandler(Player *player) : PlayerStateHandler(player){}

Rectangle MovementStateHandler::getSrc()
{
	return (Rectangle){frameX*frameWidth, 
						frameY*frameHeight+frameHeight/2, 
						frameWidth, 
						frameHeight/2};
}

Rectangle MovementStateHandler::getDest(Vector2 position)
{
	return (Rectangle){position.x-frameWidth*SIZE_MULTIPLIER/2, 
						position.y, 
						frameWidth*SIZE_MULTIPLIER, 
						frameHeight*SIZE_MULTIPLIER/2};
}

FiringStateHandler::FiringStateHandler(Player *player) : PlayerStateHandler(player)
{
}

Rectangle FiringStateHandler::getSrc()
{
	return (Rectangle){frameX*frameWidth, 
	                      frameY*frameHeight, 
						  frameWidth, 
						  frameHeight/2};
}

Rectangle FiringStateHandler::getDest(Vector2 position)
{
	return (Rectangle){position.x-frameWidth*SIZE_MULTIPLIER/2, 
	                      position.y-frameHeight*SIZE_MULTIPLIER/2, 
						  frameWidth*SIZE_MULTIPLIER, 
						  frameHeight*SIZE_MULTIPLIER/2};
}

/* ************* */
/* PLAYER STATES */
/* ************* */

PlayerState::PlayerState()
{
}

/* MOVEMENT STATES (0)*/
// Idle
void Idle::enter(PlayerStateHandler *psh, Player* player)
{
	psh->Init();
	psh->setFrameY(2);
	psh->setFrameSpeed(DEFAULT_FRAME_SPEED/2);
	player->setSpeed(PlayerConfig::DEFAULT_SPEED);
}
void Idle::exit(PlayerStateHandler *psh, Player* player) {}
void Idle::HandleInput(PlayerStateHandler *psh) 
{
	if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN))
	{
		if(IsKeyDown(KEY_LEFT_SHIFT))
			psh->setState(Focus::getInstance());
		else
			psh->setState(Moving::getInstance());
	}
}

PlayerState& Idle::getInstance()
{
	static Idle singleton;
	return singleton;
}
std::string Idle::getName() { return "IDLE"; }
Idle::Idle() : PlayerState() {}

// Focus 
void Focus::enter(PlayerStateHandler *psh, Player* player) 
{
	psh->Init();
	psh->setFrameY(2);
	psh->setFrameSpeed(DEFAULT_FRAME_SPEED);
	player->setSpeed(PlayerConfig::FOCUS_SPEED);
}
void Focus::exit(PlayerStateHandler *psh, Player* player) {}
void Focus::HandleInput(PlayerStateHandler *psh) 
{
	if(!(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN)))
		psh->setState(Idle::getInstance());

	if((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN))
	   &&!IsKeyDown(KEY_LEFT_SHIFT))
		psh->setState(Moving::getInstance());
}

PlayerState& Focus::getInstance()
{
	static Focus singleton;
	return singleton;
}
std::string Focus::getName() { return "FOCUS"; }
Focus::Focus() : PlayerState() {}

// Moving 
void Moving::enter(PlayerStateHandler *psh, Player* player) 
{
	psh->Init();
	psh->setFrameY(2);
	psh->setFrameSpeed(DEFAULT_FRAME_SPEED*2);
	player->setSpeed(PlayerConfig::DEFAULT_SPEED);
}
void Moving::exit(PlayerStateHandler *psh, Player* player) {}
void Moving::HandleInput(PlayerStateHandler *psh) 
{
	if(!(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN)))
		psh->setState(Idle::getInstance());
	if(IsKeyDown(KEY_LEFT_SHIFT))
		psh->setState(Focus::getInstance());
}

PlayerState& Moving::getInstance()
{
	static Moving singleton;
	return singleton;
}
std::string Moving::getName() { return "MOVING"; }
Moving::Moving() : PlayerState() {}

/* FIRING STATES (1)*/
// Standby
void Standby::enter(PlayerStateHandler *psh, Player* player) 
{
	psh->Init();
	psh->setFrameY(0);
	psh->setFrameSpeed(DEFAULT_FRAME_SPEED);
}
void Standby::exit(PlayerStateHandler *psh, Player* player) {}
void Standby::HandleInput(PlayerStateHandler *psh) 
{
	if(IsKeyDown(KEY_W) || IsKeyDown(KEY_Z))
		psh->setState(Firing::getInstance());
}


PlayerState& Standby::getInstance()
{
	static Standby singleton;
	return singleton;
}
std::string Standby::getName() { return "STANDBY"; }
Standby::Standby() : PlayerState() {}

// Firing
void Firing::enter(PlayerStateHandler *psh, Player* player) 
{
	psh->Init();
	psh->setFrameY(1);
	psh->setFrameSpeed(DEFAULT_FRAME_SPEED*2);
}
void Firing::exit(PlayerStateHandler *psh, Player* player) {}
void Firing::HandleInput(PlayerStateHandler *psh) 
{
	if(!(IsKeyDown(KEY_W) || IsKeyDown(KEY_Z)))
		psh->setState(Standby::getInstance());
}

PlayerState& Firing::getInstance()
{
	static Firing singleton;
	return singleton;
}
std::string Firing::getName() { return "FIRING"; }
Firing::Firing() : PlayerState() {}
