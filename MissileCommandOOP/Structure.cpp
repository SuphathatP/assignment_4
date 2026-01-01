#include "Structure.h"

Structure::Structure() : Destroyable(100)
{
	this->rubbleSpriteId = Play::GetSpriteId("rubble");
	this->structureSpriteId = -1; // invalid sprite unless set!
}

Structure::~Structure()
{

}

void Structure::Draw()
{
	if (this->IsDestroyed())
	{
		Play::DrawSprite(this->rubbleSpriteId, this->GetPosition(), 0);
	}
	else
	{
		Play::DrawSprite(this->structureSpriteId, this->GetPosition(), 0);
	}
}

void Structure::SetStructureSprite(const char* spriteName)
{
	this->structureSpriteId = Play::GetSpriteId(spriteName);
}
