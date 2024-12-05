#pragma once

enum class Stage 
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	COUNT,
};

enum class Phase
{
	ONE,TWO,THREE,FOUR,FIVE,
	SIX,SEVEN,EIGHT,NINE,TEN,
	ELEVEN,TWELVE,THIRTEEN,FOURTEEN,FIFTEEN,
	SIXTEEN,SEVENTEEN,EIGHTEEN,NINETEEN,TWENTY,
	COUNT
};

namespace Gameplay
{
	constexpr int MAX_GAME_TIMER = 99999;

	constexpr int INITIAL_LIVES = 99;
	constexpr int INITIAL_BOMBS = 3;
	constexpr int INITIAL_POWER = 1;

	constexpr int HIT_COOLDOWN   = 2.0f;
	
	enum class Dir
	{
		NORTH,
		EAST,
		SOUTH,
		WEST,
	};

	constexpr float NORTH_ROT = 270.0f;
	constexpr float EAST_ROT  = 0.0f;
	constexpr float SOUTH_ROT = 90.0f;
	constexpr float WEST_ROT  = 180.0f;
}