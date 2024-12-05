#pragma once

#include <raylib.h>
#include <array>
#include <vector>
#include <unordered_map>

#include "../../../include/constants/enemy_constants.h"
#include "../../../include/constants/gameplay_constants.h"
#include "../../../include/constants/graphics_constants.h"

class Game;

class TextureManager
{
private:
	std::unordered_map<TextureID, Texture2D> textures;
public:
	TextureManager();

	Texture2D* getTexture(TextureID id);

	~TextureManager();
};