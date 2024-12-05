#pragma once

// Librairies
#include <unordered_map>
#include <vector>
#include <raylib.h>

// Constants
#include "../../../include/constants/gameplay_constants.h"

class Game;
class ParallaxLayer;

class BackgroundManager
{
private:
	Game* game;

	std::unordered_map<Stage, std::vector<ParallaxLayer*>> backgrounds;
public:
	BackgroundManager(Game* game);
	void Init();
	void Update(float deltaTime);
	void Draw();
	~BackgroundManager() = default;
};

class ParallaxLayer
{
private:
	Texture2D* texture;
    float speed;    
    Vector2 position;

public:
	ParallaxLayer(Texture2D* texture, float speed);
	void Init();
	void Update(float deltaTime);
	void Draw();
	~ParallaxLayer() = default;
};