#pragma once

constexpr int FPS = 60;

constexpr int WINDOW_WIDTH  = (int)(1600 * 1.0);
constexpr int WINDOW_HEIGHT = (int)(900 * 1.0);

constexpr int GAME_X      = (int)(WINDOW_WIDTH  * 0.10);
constexpr int GAME_Y      = (int)(WINDOW_HEIGHT * 0.02);
constexpr int GAME_WIDTH  = (int)(WINDOW_WIDTH  * 0.45);
constexpr int GAME_HEIGHT = (int)(WINDOW_HEIGHT * 0.96);

constexpr int GAME_UI_X      = GAME_X + GAME_WIDTH + 50;
constexpr int GAME_UI_Y      = GAME_Y;
constexpr int GAME_UI_WIDTH  = (int)(WINDOW_WIDTH  * 0.30);
constexpr int GAME_UI_HEIGHT = (int)(WINDOW_HEIGHT * 0.96);

constexpr int DEFAULT_FRAME_SPEED = 4;
constexpr float SIZE_MULTIPLIER   = 1.5f;

enum class TextureID 
{
	/* Entities */
	BULLET, 
	PLAYER, 
	GE1,    
	GE2,    
	SPAWNER,
	/* Backgrounds */
	// Stage 1
	S1_BASE_BLACK,     
	S1_NEBULA_YELLOW_1,
	S1_NEBULA_YELLOW_2,
	S1_NEBULA_YELLOW_3,
	S1_NEBULA_BLACK, 
	S1_NEBULA_WHITE, 
	S1_STARS_1,        
	S1_STARS_2,        
	COUNT
};
