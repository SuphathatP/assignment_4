#pragma once
#include "constants.h"
#include "Play.h"
#include "lib/LinkedList.h"


using namespace Play;


//struct SpriteObj {
//	Vector2f pos;
//	int spriteId;
//	SpriteObj(int spriteId, Vector2f pos)
//		: spriteId(spriteId), pos(pos) {
//	}
//};

struct Missile {
	Vector2f pos;
	Vector2f origin;
	Vector2f target;

	Missile(Vector2f origin, Vector2f target);
};

void draw();
void drawCursor();
void drawBuildings();

void init();
void setupBuildings();