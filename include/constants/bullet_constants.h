#pragma once

namespace BulletConfig
{
	enum class Type 
	{
		PLAYER,
		TINY,
		SMALL,
		MEDIUM,
		LARGE,
		COUNT,
	};

	constexpr float DEFAULT_BULLET_SPEED   = 500.0f;

	constexpr float PLAYER_HITBOX          = 10.0f;
	constexpr float PLAYER_BULLET_SPEED    = 700.0f;
	constexpr float PLAYER_BULLET_ROTATION = 270.0f;

	constexpr int   POINTS = 10;

	constexpr float TINY_HITBOX   = 2.0f;

	constexpr float SMALL_HITBOX  = 4.0f;

	constexpr float MEDIUM_HITBOX = 10.0f;

	constexpr float LARGE_HITBOX  = 20.0f;
	
}