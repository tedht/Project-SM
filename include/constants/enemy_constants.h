#pragma once

namespace EnemyConfig
{
	enum class Type 
	{
		GENERIC_1,
		GENERIC_2,
		COUNT
	};

	constexpr int   DEFAULT_HP             = 1;
	constexpr int   DEFAULT_POINTS         = 1000;
	constexpr float DEFAULT_ROTATION       = 0.0f;
	constexpr float DEFAULT_SPEED          = 200.0f;
	constexpr float DEFAULT_HITBOX         = 40.0f;
	constexpr float DEFAULT_SHOOT_COOLDOWN = 0.05;

	constexpr float GENERC_1_SPEED = 200.0f;
	constexpr float GENERC_2_SPEED = 200.0f;
}