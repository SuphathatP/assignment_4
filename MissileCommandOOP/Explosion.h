#pragma once
#include "GameObject.h"

const Play::Colour EXPLOTION_COLORS[4] = {
	{ 100.0f, 100.0f, 100.0f },//Play::cWhite,
	{ 100.0f, 0.0f, 0.0f },    //Play::cRed,
	{ 0.0f, 0.0f, 100.0f },    //Play::cBlue,
	{ 100.0f, 100.0f, 0.0f }   //Play::cYellow
};

class Explosion : public GameObject
{
public:
	Explosion(Play::Point2D position);

	void Simulate(float elapsedTime) override;

	void Draw() override;

private:
	float currentRadius;
	float maxRadius;
	int alternateColour;

	void Explode();

	bool hasExploded;
};

