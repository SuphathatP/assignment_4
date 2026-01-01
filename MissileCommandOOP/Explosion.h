#pragma once
#include "GameObject.h"

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

