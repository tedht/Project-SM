// Librairies
#include <raylib.h>
#include <iostream>

// Classes
#include "BackgroundManager.h"
#include "../Game.h"

BackgroundManager::BackgroundManager(Game *game) : game(game)
{
	/* Stage 1 */
	backgrounds[Stage::ONE].push_back(new ParallaxLayer(game->getTexture(TextureID::S1_BASE_BLACK), 0));
	backgrounds[Stage::ONE].push_back(new ParallaxLayer(game->getTexture(TextureID::S1_NEBULA_YELLOW_1), 10.0f));
	backgrounds[Stage::ONE].push_back(new ParallaxLayer(game->getTexture(TextureID::S1_NEBULA_YELLOW_2), 20.0f));
	backgrounds[Stage::ONE].push_back(new ParallaxLayer(game->getTexture(TextureID::S1_NEBULA_YELLOW_3), 30.0f));
	backgrounds[Stage::ONE].push_back(new ParallaxLayer(game->getTexture(TextureID::S1_NEBULA_BLACK), 25.0f));
	backgrounds[Stage::ONE].push_back(new ParallaxLayer(game->getTexture(TextureID::S1_NEBULA_WHITE), 25.0f));
	backgrounds[Stage::ONE].push_back(new ParallaxLayer(game->getTexture(TextureID::S1_STARS_1), 15.0f));
	backgrounds[Stage::ONE].push_back(new ParallaxLayer(game->getTexture(TextureID::S1_STARS_2), 5.0f));

	/* Stage 2 */
	/* Stage 3 */
	/* Stage 4 */
	/* Stage 5 */
	/* Stage 6 */
	/* Stage 7 */

	Init();
}

void BackgroundManager::Init()
{
	for(size_t i = 0; i < static_cast<size_t>(Stage::COUNT); i++)
	{
		for(size_t j = 0; j < backgrounds[static_cast<Stage>(i)].size(); j++)
		{
			backgrounds[static_cast<Stage>(i)][j]->Init();
		}
	}
}

void BackgroundManager::Update(float deltaTime)
{
	for(size_t i = 0; i < backgrounds[game->getStage()].size(); i++)
	{
		backgrounds[game->getStage()][i]->Update(deltaTime);
	}
}

void BackgroundManager::Draw()
{
	for(size_t i = 0; i < backgrounds[game->getStage()].size(); i++)
	{
		backgrounds[game->getStage()][i]->Draw();
	}
}

ParallaxLayer::ParallaxLayer(Texture2D* texture, float speed) : texture(texture), speed(speed)
{
	Init();
}

void ParallaxLayer::Init()
{
	position = Vector2{0, (float)GetScreenHeight()-texture->height};
}

void ParallaxLayer::Update(float deltaTime)
{
	position.y += speed * deltaTime;

	if (position.y >= GetScreenHeight()) 
	{
        position.y = GetScreenHeight()-texture->height;
    }

}

void ParallaxLayer::Draw()
{
	DrawTexture(*texture, (int)position.x, (int)position.y, WHITE);
	DrawTexture(*texture, (int)position.x, (int)(position.y-texture->height-1), WHITE);
}
