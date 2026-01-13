#include "game.h"

int SPRITE_RUBBLE;
int SPRITE_CITY;
int SPRITE_BASE;

// added and removed all the time
LinkedList<Missile> missiles;

// never changes size
Vector2f building_pos[COUNT_BUILDINGS];
char building_health[COUNT_BUILDINGS]; // range(char) = (-128, +127) and since max health is 100, we don't need more space
int base_missile_count[COUNT_BASES];

Missile::Missile(Vector2f origin, Vector2f target)
	: pos(origin), origin(origin), target(target)
	, isHostile(origin.y - target.y > 0){}
/* void explode(pos, int i) {
*	spawn_explosion(pos);
*	// missiles.remove(i); // could be buggy
*	
}

void explode(pos) {
*	spawn_explotion(pos);
*	missiles.pop_front();
} */

void init() {
	SPRITE_RUBBLE = Play::GetSpriteId("rubble");
	SPRITE_CITY = Play::GetSpriteId("city");
	SPRITE_BASE = Play::GetSpriteId("missile_base");

	//setup buildings
	float offset = (float)DISPLAY_WIDTH / 7.0f;
	for (size_t i = 0; i < COUNT_BASES; i++)
	{
		// base
		building_pos[i] = Play::Point2D((offset * i * 2.0f) + offset * 1.4f, GROUND_Y);
		building_health[i] = 100; // BASE_MAX_HEALTH
		base_missile_count[i] = 10;
	}
	for (size_t i = COUNT_BASES; i < COUNT_BUILDINGS; i++) {
		// city
		//								(i-3) * offset + offset
		//								offset * ((i - 3) + 1)
		//								offset * (i - 2)
		building_pos[i] = Play::Point2D(offset * (i - 2), GROUND_Y);
		building_health[i] = MISSILE_DAMAGE - 1; // one shot one kill
	}
}

void SpawnPlayerMissile(Vector2f target_pos) {
	// squared distance is faster
	float best_dist_sqrd = FLT_MAX; // FLOAT_MAX = 3.40282e+38
	int best_index = -1;
	for (int i = 0; i < COUNT_BASES; i++)
	{
		if (building_health[i] <= 0 || base_missile_count[i] <= 0)
			continue;

		float dist = (building_pos[i] - target_pos).LengthSqr();
		if(dist < best_dist_sqrd) {
			best_dist_sqrd = dist;
			best_index = i;
		}
	}
	if (best_index == -1) return;

	// pushing in front is (generally) faster for linked lists (depends on if they store the tail or not)
	missiles.push_front(Missile(building_pos[best_index], target_pos));
	base_missile_count[best_index]--;
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
	missiles.forEach([](Missile missile) {
		Colour color = (missile.isHostile) ? cMagenta : cYellow;
		DrawCircle(missile.target, 2, color);
		DrawLine(missile.origin, missile.pos, color);
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