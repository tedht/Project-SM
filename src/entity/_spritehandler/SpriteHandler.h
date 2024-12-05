#pragma once

#include <raylib.h>
	
class SpriteHandler
{
protected:
	Texture2D* texture;
	int frameSpeed; 
	int rows;
	int cols;

	float frameWidth;
	float frameHeight;

	float frameX;
	float frameY;
	int   maxFrameX;
	int   maxFrameY;
    int   framesCounter;
public:
    SpriteHandler();

	void Init();
	void Update();
    void Draw(Vector2 position);

	Rectangle getSrc();
	Rectangle getDest(Vector2 position);

	int getFrameX();
	int getFrameY();

	Texture2D* getTexture();

	void setSprite(Texture2D *texture);
	void setSprite(Texture2D *texture, int rows, int cols);

	void setFrameX(int frameX);
	void setFrameY(int frameY);

	virtual ~SpriteHandler() = default;
};