#pragma once
#include "constants.h"
#include "Play.h"
#include "lib/LinkedList.h"

using namespace Play;

struct Missile {
	Vector2f pos;
	Vector2f origin;
	Vector2f target;
	bool isHostile;

	Missile(Vector2f origin, Vector2f target);
};

void draw();
void drawCursor();
void drawBuildings();

void init();
//void setupBuildings();