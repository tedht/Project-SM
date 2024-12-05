#include "Utils.h"

#include <cstdlib>
#include <cmath>
#include <random>

int getRandomValue(int min, int max) 
{
    return min + rand() % ((max + 1) - min);
}

float getRandomValue(float min, float max) {
    float scale = rand() / static_cast<float>(RAND_MAX);
    return min + scale * (max - min);
}

float distance(Vector2 pos1, Vector2 pos2)
{
    return distance(pos1.x, pos1.y, pos2.x, pos2.y);
}

float distance(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

float calculateAngle(Vector2 pos1, Vector2 pos2)
{
	float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    float angle = atan2(dy, dx) * (180.0f / PI);  // Convert radians to degrees
    return angle;
}

int randomInt(int min, int max) 
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}

float dirToRot(Gameplay::Dir dir)
{
	switch (dir)
	{
	case Gameplay::Dir::NORTH: return Gameplay::NORTH_ROT;
	case Gameplay::Dir::EAST:  return Gameplay::EAST_ROT;
	case Gameplay::Dir::SOUTH: return Gameplay::SOUTH_ROT;
	case Gameplay::Dir::WEST:  return Gameplay::WEST_ROT;
	default: return -1;
	}
}

float degreesToRad(float degrees)
{
	return degrees * PI / 180.0f;
}

float randomFloat() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> distrib(0.0f, 1.0f);
    return distrib(gen);
}