#include "game.h"
#include "lib/LinkedList.h"

using namespace Play;

// added and removed all the time

struct GameObj {
	Play::Vector2f pos;
	/*collition*/
	//float radius;
	//virtual void Draw() = 0;

	GameObj(Play::Vector2f pos/*,float radius*/) : pos(pos)/*, radius(radius)*/{}
	//GameObj() :pos({0,0}) {}
};

struct SpriteObj : public GameObj {
	int spriteId;
	void Draw() {
		Play::DrawSprite(spriteId, pos, 0);
	}

	SpriteObj(int spriteId, Play::Vector2f pos) 
		: spriteId(spriteId), GameObj(pos) { }
};

struct Missile : public GameObj {
	int spriteId;
	Play::Vector2f origin;
	Play::Vector2f target;
	bool isPlayerOwned;


	//void Draw() {
	//	DrawLine(origin, pos, cRed);
	//	DrawCircle(target, radius, cBlue);
	//}

	Missile(Play::Vector2f pos, bool isPlayerOwned) :  GameObj(pos), isPlayerOwned(isPlayerOwned) {}
};

LinkedList<Missile> missiles;

void drawMissliles() {
	missiles.forEach([](Missile missile) {
		Colour targetColor = missile.isPlayerOwned? cBlue: cRed;
		if (!missile.isPlayerOwned) {
			DrawLine(missile.origin, missile.pos, cRed);
		}
		DrawCircle(missile.target, 2, targetColor);
	});
}

/* 
# alt:
- no Missile.isPlayerOwned
*/
LinkedList<Missile> PlayerMissiles;
LinkedList<Missile> EnemyMissiles;

Vector2f Buildings[6+3];

void setupBuildings() {
	int offset = DISPLAY_WIDTH / 7;
	for (size_t i = 0; i < 6; i++)
	{
		Buildings[i] = Play::Point2D(float(i) * offset + offset, 16);
	}
	for (size_t i = 6; i < 9; i++) {
		Buildings[i]=Play::Point2D((offset * (i-6) * 2.0f) + offset * 1.4f, 16);
	}
	//	for (size_t i = 0; i < 3; i++)
	//{
	//	
	//}
}

void drawCursor(){
	// cursor
	Vector2f mousePos = Play::Input::GetMousePos();
	Vector2f offsetX = { 2,0 };
	Vector2f offsetY = { 0,2 };
	DrawRect(mousePos - offsetX, mousePos + offsetX, cCyan);
	DrawRect(mousePos - offsetY, mousePos + offsetY, cCyan);
}

void draw() {
	// missiles
	PlayerMissiles.forEach([](Missile missile) {
		DrawCircle(missile.target, 2, cBlue);
	});
	EnemyMissiles.forEach([](Missile missile) {
		DrawLine(missile.origin, missile.pos, cRed);
		DrawCircle(missile.target, 2, cRed);
	});


	drawCursor();
}

