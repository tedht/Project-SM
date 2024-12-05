#include <iostream>

#include "TextureManager.h"

TextureManager::TextureManager()
{
	/* Entities */
	textures[TextureID::BULLET]  = LoadTexture("assets/sprites/entity/bullet/Bullets.png"); 
	textures[TextureID::PLAYER]  = LoadTexture("assets/sprites/entity/player/Jet1.1.png");
	textures[TextureID::GE1]     = LoadTexture("assets/sprites/entity/enemy/GenericEnemy1.1.png");
	textures[TextureID::GE2]     = LoadTexture("assets/sprites/entity/enemy/GenericEnemy2.1.png");
	textures[TextureID::SPAWNER] = LoadTexture("assets/sprites/entity/_spawner/Spawners.png");

	/* Backgrounds */
	// Stage 1
	textures[TextureID::S1_BASE_BLACK]      = (LoadTexture("assets/sprites/background/stage_1/base_black.png"));
	textures[TextureID::S1_NEBULA_YELLOW_1] = (LoadTexture("assets/sprites/background/stage_1/nebula_yellow_1.png"));
	textures[TextureID::S1_NEBULA_YELLOW_2] = (LoadTexture("assets/sprites/background/stage_1/nebula_yellow_2.png"));
	textures[TextureID::S1_NEBULA_YELLOW_3] = (LoadTexture("assets/sprites/background/stage_1/nebula_yellow_3.png"));
	textures[TextureID::S1_NEBULA_BLACK]    = (LoadTexture("assets/sprites/background/stage_1/nebula_black.png"));
	textures[TextureID::S1_NEBULA_WHITE]    = (LoadTexture("assets/sprites/background/stage_1/nebula_white.png"));
	textures[TextureID::S1_STARS_1]         = (LoadTexture("assets/sprites/background/stage_1/stars_1.png"));
	textures[TextureID::S1_STARS_2]         = (LoadTexture("assets/sprites/background/stage_1/stars_2.png"));
}

Texture2D *TextureManager::getTexture(TextureID id) { return &textures[id]; }

TextureManager::~TextureManager()
{
	for(int i = 0; i < static_cast<int>(TextureID::COUNT); i++)
	{
		UnloadTexture(textures[static_cast<TextureID>(i)]);
	}
}
