#pragma once
#include "Destroyable.h"

class Structure : public Destroyable
{
public:
	Structure(int spriteId = -1);
	~Structure();

	void Draw() override;

	void SetStructureSprite(const char* spriteName);

private:
	int rubbleSpriteId;
	int structureSpriteId;
};
