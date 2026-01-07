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
	speed(speed),
	state(MISSILE_STATE::TRAVELING),
	// expl{
	maxRadius(16.0f),
	currentRadius(maxRadius / 2.0f),
	expansionSpeed(maxRadius * 6.0f)
	// }
	//_dt(-12)
{
	this->SetPosition(origin);
}

void Missile::Draw()
{
	switch (this->state) {
	case TRAVELING: {
		Play::Vector2D direction = this->GetTravellingDirection();

		Play::Point2D endPoint = this->origin + direction * distanceTravelled;

		Play::DrawLine(this->origin, endPoint, this->colour);

		this->alternateColour = (this->alternateColour + 1) % 8;
		int colourIndex = this->alternateColour / 2;

		Play::DrawPixel(endPoint, EXPLOTION_COLORS[colourIndex]);

		// Draw Target
		Play::DrawCircle(this->target, 2, this->colour);
		break;
	}

	case EXPLODING: {

		this->alternateColour = (this->alternateColour + 1) % 8;
		int colourIndex = this->alternateColour / 2;

		Play::DrawCircle(this->position, this->currentRadius, EXPLOTION_COLORS[colourIndex]);
		break;
	}
	//case DEAD: {
	//	break;
	//}
	}
}

void Missile::Simulate(float elapsedTime)
{
	//this->_dt = elapsedTime;
		Play::Vector2D direction = this->GetTravellingDirection();
		Play::Point2D currentPosition = this->origin + direction * distanceTravelled;
		this->SetPosition(currentPosition);
	switch (this->state) {
	case TRAVELING: {

		this->distanceTravelled += this->speed * elapsedTime;

		if (this->IsDestroyed() || distanceTravelled >= GetDistanceFromOriginToTarget())
		{
			state = EXPLODING;
			Explosion* explosion = new Explosion(this->GetPosition());
			this->gameStateManager->AddGameObject(explosion);

			// Destroy this object
			//this->ScheduleDelete();
		}
		break;
	case EXPLODING: {
		const float expansionSpeed2 = this->expansionSpeed * elapsedTime;
		currentRadius = std::fminf(this->currentRadius + expansionSpeed2, maxRadius);
		break;
	}
	}
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
