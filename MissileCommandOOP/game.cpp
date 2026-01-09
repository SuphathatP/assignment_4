#include "game.h"

int SPRITE_RUBBLE;
int SPRITE_CITY;
int SPRITE_BASE;

// added and removed all the time
LinkedList<Missile> playerMissiles;
LinkedList<Missile> hostileMissiles;

// never changes size
Vector2f building_pos[COUNT_BUILDINGS];
int building_health[COUNT_BUILDINGS]; // 
int building_missiles[COUNT_BASES];

void init() {
	SPRITE_RUBBLE = Play::GetSpriteId("rubble");
	SPRITE_CITY = Play::GetSpriteId("city");
	SPRITE_BASE = Play::GetSpriteId("missile_base");
	setupBuildings();
}

Missile::Missile(Vector2f origin, Vector2f target)
	: pos(origin), origin(origin), target(target) {
}


void SpawnPlayerMissile(Vector2f target_pos){
	// squared distance is faster
	float best_dist_sqrd = 1e9f;
	int best_index = -1;
	for (int i = 0; i < 3; i++)
	{
		if (building_health[i] <= 0 || building_missiles[i] <= 0)
			continue;
		float dist = (building_pos[i] - target_pos).LengthSqr();
		if(dist < best_dist_sqrd){
			best_dist_sqrd = dist;
			best_index = i;
		}
	}
	if (best_index == -1) return;

	// pushing in front is *generally* faster for linked lists, depends if they store the tail or not
	playerMissiles.push_front(Missile(building_pos[best_index],target_pos));
	building_missiles[best_index]--;
}


void setupBuildings() {
	float offset = (float)DISPLAY_WIDTH / 7.0f;
	for (size_t i = 0; i < 3; i++)
	{
		// base
		building_pos[i] = Play::Point2D((offset * i * 2.0f) + offset * 1.4f, GROUND_Y);
		building_health[i] = 100; // BASE_HEALTH
		building_missiles[i] = 10;
	}
	for (size_t i = 3; i < 9; i++) {
		// city
		//								(i-3) * offset + offset
		building_pos[i] = Play::Point2D(offset * ((i - 3) + 1), GROUND_Y);
		building_health[i] = 1; // weak
	}

}
 
void drawBuildings() {

	for (int i = 0; i < 9; i++)
	{
		if (building_health[i] < 0) {
			DrawSprite(SPRITE_RUBBLE, building_pos[i], 0);
			return;
		}

		DrawSprite((i < 3) ? SPRITE_BASE : SPRITE_CITY, building_pos[i], 0);
	}
}

void draw() {
	// missiles
	playerMissiles.forEach([](Missile missile) {
		DrawCircle(missile.target, 2, Play::cMagenta);
		DrawLine(missile.origin, missile.pos, Play::cMagenta);
	});
	hostileMissiles.forEach([](Missile missile) {
		DrawCircle(missile.target, 2, Play::cYellow);
		DrawLine(missile.origin, missile.pos, Play::cYellow);
	});

	drawBuildings();
	drawCursor();
}

void drawCursor() {
	// cursor
	Vector2f mousePos = Play::Input::GetMousePos();
	Vector2f offsetX = { 2,0 };
	Vector2f offsetY = { 0,2 };
	DrawLine(mousePos - offsetX, mousePos + offsetX, cCyan);
	DrawLine(mousePos - offsetY, mousePos + offsetY, cCyan);
}