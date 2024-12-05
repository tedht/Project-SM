#include "SpriteHandler.h"
#include "../../../include/constants/graphics_constants.h"

#include <iostream>

Rectangle SpriteHandler::getSrc()
{
	return (Rectangle){frameX*frameWidth, frameY*frameHeight, frameWidth, frameHeight};
}

Rectangle SpriteHandler::getDest(Vector2 position)
{
	return (Rectangle){position.x, 
                       position.y, 
                       frameWidth*SIZE_MULTIPLIER, 
                       frameHeight*SIZE_MULTIPLIER};
}

int SpriteHandler::getFrameX(){return frameX;}
int SpriteHandler::getFrameY(){return frameY;}

Texture2D *SpriteHandler::getTexture(){return texture;}

SpriteHandler::SpriteHandler()
: frameSpeed(DEFAULT_FRAME_SPEED), rows(1), cols(1),
frameWidth(0), frameHeight(0), frameX(0), frameY(0), maxFrameX(0), maxFrameY(0), framesCounter(0)
{
}

void SpriteHandler::Init()
{
	frameX = 0;
    frameY = 0;
    framesCounter = 0;

	frameSpeed = DEFAULT_FRAME_SPEED;
}

void SpriteHandler::Update()
{
	framesCounter++;
	if (framesCounter >= (60/frameSpeed))
	{
		framesCounter = 0;
		frameX++;
		if (frameX > maxFrameX) frameX = 0;
	}
}

void SpriteHandler::Draw(Vector2 position)
{
	if(texture->id == 0)
	{
		std::cout << "Textures not loaded\n";
	}
	DrawTexturePro(*texture, 
					getSrc(),
					getDest(position),
					(Vector2){frameWidth*SIZE_MULTIPLIER/2, frameHeight*SIZE_MULTIPLIER/2}, 
					0, 
					WHITE);
}

void SpriteHandler::setSprite(Texture2D *texture)
{
	setSprite(texture, 1, 1);
}

void SpriteHandler::setSprite(Texture2D *texture, int rows, int cols)
{
	this->texture    = texture;
	this->rows       = rows;
	this->cols       = cols;

	frameWidth  = (float)texture->width/cols;
	frameHeight = (float)texture->height/rows;
	maxFrameX   = cols-1;
	maxFrameY   = rows-1;
}

void SpriteHandler::setFrameX(int frameX){this->frameX = frameX;}
void SpriteHandler::setFrameY(int frameY){this->frameY = frameY;}
