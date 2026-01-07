#include "Explosion.h"
#include "GameStateManager.h"
#include "Destroyable.h"

struct Expl {
	float currentRadius;
	float maxRadius;
};

Explosion::Explosion(Play::Point2D position) :
	hasExploded(false),
	maxRadius(16.0f),
	currentRadius(maxRadius / 2.0f),
	alternateColour(0)
{
	this->SetPosition(position);
}

void Explosion::Simulate(float elapsedTime)
{
	if (!this->hasExploded)
	{
		Explode();
	}

	// simulate explosion for x seconds, then schedule for deletion.
	const float expansionSpeed = maxRadius * 6.0f * elapsedTime;
	currentRadius = std::fminf(this->currentRadius + expansionSpeed, maxRadius);

	if (currentRadius == maxRadius)
	{
		this->ScheduleDelete();
	}
}

void Explosion::Draw()
{
	//this->alternateColour = (this->alternateColour + 1) % 8;
	//int colourIndex = this->alternateColour / 2;

	//Play::DrawCircle(this->position, this->currentRadius, EXPLOTION_COLORS[colourIndex]);
}

void Explosion::Explode()
{
	Play::PlayAudio("Explode");

	GameObject* object = this->gameStateManager->GetFirstGameObject();
	while (object != nullptr)
	{
		Destroyable* destroyable = dynamic_cast<Destroyable*>(object);
		if (destroyable != nullptr)
		{
			// the object is destroyable, reduce health if within max radius
			if ((destroyable->GetPosition() - this->GetPosition()).Length() < this->maxRadius)
			{
				destroyable->ReduceHealth(50);
			}
		}
		object = object->GetNextActiveGameObject();
	}

	this->hasExploded = true;
}
