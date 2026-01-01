#pragma once
#include "GameObject.h"

class MissileBase;

class Reticle : public GameObject
{
public:
	void Simulate(float elapsedTime) override;
	void Draw() override;

private:
	MissileBase* GetClosestMissileBase(Play::Point2D targetPosition) const;

	bool fired = false;
};

