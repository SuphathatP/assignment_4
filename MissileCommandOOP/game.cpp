#include "game.h"
#include "lib/LinkedList.h"

using namespace Play;

// added and removed all the time

struct GameObj {
	Vector2f pos;
	/*collition*/
	//float radius;
	//virtual void Draw() = 0;

	GameObj(Vector2f pos/*,float radius*/) : pos(pos)/*, radius(radius)*/{}
	//GameObj() :pos({0,0}) {}
};

struct SpriteObj : public GameObj {
	int spriteId;
	//void Draw() {
	//	Play::DrawSprite(spriteId, pos, 0);
	//}

	SpriteObj(int spriteId, Vector2f pos) 
		: spriteId(spriteId), GameObj(pos) { }
};

struct Missile {
	Vector2f pos;
	Vector2f origin;
	Vector2f target;

	Missile(Vector2f origin, Vector2f target) 
		: pos(origin), origin(origin), target(target) {
	}
};


LinkedList<Missile> playerMissiles;
LinkedList<Missile> hostileMissiles; // idk how to spell, ok?

// base + city
Vector2f building_pos[3+6];
int buildingHealth[3+6];
int buildingMissiles[3];

void SpawnPlayerMissile(Vector2f target_pos){
	// squared distance is faster
	float best_dist_sqrd = 1e9f;
	int best_index = -1;
	for (int i = 0; i < 3; i++)
	{
		if (buildingHealth[i] <= 0 || buildingMissiles[i] <= 0)
			continue;
		float dist = (building_pos[i] - target_pos).LengthSqr();
		if(dist<best_dist_sqrd){
			best_dist_sqrd = dist;
			best_index = i;
		}
	}
}


void setupBuildings() {
	int offset = DISPLAY_WIDTH / 7;
	for (size_t i = 0; i < 3; i++)
	{
		// city
		building_pos[i] = Play::Point2D(float(i) * offset + offset, 16);
		buildingHealth[i] = 50;
		buildingMissiles[i] = 10;
	}
	for (size_t i = 3; i < 9; i++) {
		// base
		building_pos[i] = Play::Point2D((offset * (i-6) * 2.0f) + offset * 1.4f, 16);
		buildingHealth[i] = 100;
	}
	//	for (size_t i = 0; i < 3; i++)
	//{
	//	
	//}
}

void draw() {
	// missiles
	playerMissiles.forEach([](Missile missile) {
		DrawCircle(missile.target, 2, cBlue);
		DrawLine(missile.origin, missile.pos, cBlue);
	});
	hostileMissiles.forEach([](Missile missile) {
		DrawCircle(missile.target, 2, cRed);
		DrawLine(missile.origin, missile.pos, cRed);
	});


	drawCursor();
}

void drawCursor() {
	// cursor
	Vector2f mousePos = Play::Input::GetMousePos();
	Vector2f offsetX = { 2,0 };
	Vector2f offsetY = { 0,2 };
	DrawRect(mousePos - offsetX, mousePos + offsetX, cCyan);
	DrawRect(mousePos - offsetY, mousePos + offsetY, cCyan);
}