#pragma once

#include <raylib.h>
#include "../../include/constants/gameplay_constants.h"

int getRandomValue(int min, int max);
float getRandomValue(float min, float max);

float distance(Vector2 pos1, Vector2 pos2);
float distance(float x1, float y1, float x2, float y2);
float calculateAngle(Vector2 pos1, Vector2 pos2);

int randomInt(int min, int max);

float dirToRot(Gameplay::Dir dir);
float degreesToRad(float degrees);
