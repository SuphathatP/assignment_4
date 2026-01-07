#pragma once
#include "Destroyable.h"

enum MISSILE_STATE {
	TRAVELING,
	EXPLODING,
	DEAD
};


class Missile : public Destroyable
{
public:
	Missile(Play::Point2D origin, Play::Point2D target, Play::Colour colour, float speed);

	void Draw() override;

	void Simulate(float elapsedTime) override;

	Play::Vector2D GetTravellingDirection() const;
	
	float GetDistanceFromOriginToTarget() const;

private:
	Play::Colour colour;
	Play::Point2D origin;
	Play::Point2D target;
	float distanceTravelled;
	int alternateColour;
	float speed;
	MISSILE_STATE state;
	// explotion {
	float currentRadius;
	float maxRadius;
	float expansionSpeed;
	//float _dt;
	// }
};

