#include "Missile.h"
#include "Explosion.h"
#include "GameStateManager.h"

Missile::Missile(Play::Point2D origin, Play::Point2D target, Play::Colour colour, float speed) :
	Destroyable(1),
	origin(origin),
	target(target),
	colour(colour),
	distanceTravelled(0),
	alternateColour(0),
	speed(speed)
{
	this->SetPosition(origin);
}

void Missile::Draw()
{
	Play::Vector2D direction = this->GetTravellingDirection();

	Play::Point2D endPoint = this->origin + direction * distanceTravelled;
	
	Play::DrawLine(this->origin, endPoint, this->colour);

	const Play::Colour colours[4] = {
		Play::cWhite,
		Play::cRed,
		Play::cBlue,
		Play::cYellow
	};

	this->alternateColour = (this->alternateColour + 1) % 8;
	int colourIndex = this->alternateColour / 2;

	Play::DrawPixel(endPoint, colours[colourIndex]);

	// Draw Target
	Play::DrawCircle(this->target, 2, this->colour);
}

void Missile::Simulate(float elapsedTime)
{
	this->distanceTravelled += this->speed * elapsedTime;
	Play::Vector2D direction = this->GetTravellingDirection();
	Play::Point2D currentPosition = this->origin + direction * distanceTravelled;
	this->SetPosition(currentPosition);

	if (distanceTravelled >= GetDistanceFromOriginToTarget() || this->IsDestroyed())
	{
		Explosion* explosion = new Explosion(this->GetPosition());
		this->gameStateManager->AddGameObject(explosion);
		
		// Destroy this object
		this->ScheduleDelete();
	}
}

Play::Vector2D Missile::GetTravellingDirection() const
{
	Play::Vector2D direction = (this->target - this->origin);
	direction.Normalize();
	return direction;
}

float Missile::GetDistanceFromOriginToTarget() const
{
	return (this->target - this->origin).Length();
}
