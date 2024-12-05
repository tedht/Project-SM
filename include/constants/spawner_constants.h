#pragma once

namespace SpawnerConfig
{
	enum class Type 
	{
		STRAIGHT,
		TARGETED,
		ROTATING,
		PARABOLIC_CURVE,
		COUNT,
	};

	constexpr float DEFAULT_ROTATION = 0.0f;
	constexpr float DEFAULT_SPEED    = 5.0f;
	constexpr float DEFAULT_HITBOX   = 5.0f;
	constexpr float DEFAULT_COOLDOWN = 0.5f;
}