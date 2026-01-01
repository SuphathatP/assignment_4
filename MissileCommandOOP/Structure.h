#pragma once
#include "Destroyable.h"

class Structure : public Destroyable
{
public:
	Structure();
	~Structure();

	void Draw() override;

	void SetStructureSprite(const char* spriteName);

private:
	int rubbleSpriteId;
	int structureSpriteId;
};
