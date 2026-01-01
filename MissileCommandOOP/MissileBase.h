#pragma once
#include "Structure.h"

class MissileBase : public Structure
{
public:
	MissileBase();

	void Draw() override;

	void Simulate(float elapsedTime) override;

	void FireMissile(Play::Point2D target);

private:
	int maxMissiles;
	int missileCount;
	float missileSpeed;
	float timeSinceReload;
	float reloadTime;
};

