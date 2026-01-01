#include "Reticle.h"
#include "Missile.h"
#include "MissileBase.h"
#include "GameStateManager.h"

void Reticle::Simulate(float elapsedTime)
{
	this->SetPosition(Play::Input::GetMousePos());

	if (Play::Input::GetMouseDown(Play::Input::MouseButton::BUTTON_LEFT) && !this->fired)
	{
		this->fired = true;
		MissileBase* closestBase = this->GetClosestMissileBase(this->GetPosition());
		if (closestBase != nullptr)
		{
			closestBase->FireMissile(this->GetPosition());
		}
	}
	if (!Play::Input::GetMouseDown(Play::Input::MouseButton::BUTTON_LEFT))
	{
		this->fired = false;
	}
}

void Reticle::Draw()
{
	const int reticleHalfSize = 2; // half (size - 1)
	Play::DrawLine(this->GetPosition() + Play::Vector2D(-reticleHalfSize, 0), this->GetPosition() + Play::Vector2D(reticleHalfSize, 0), Play::cGreen);
	Play::DrawLine(this->GetPosition() + Play::Vector2D(0, reticleHalfSize), this->GetPosition() + Play::Vector2D(0, -reticleHalfSize), Play::cGreen);
}

MissileBase* Reticle::GetClosestMissileBase(Play::Point2D targetPosition) const
{
	MissileBase* closestBase = nullptr;
	float closestDistance = 9999999999.0f;
	GameObject* object = this->gameStateManager->GetFirstGameObject();
	while (object != nullptr)
	{
		MissileBase* base = dynamic_cast<MissileBase*>(object);
		if (base != nullptr && !base->IsDestroyed())
		{
			// the object is a base, check for the closest
			float distance = (base->GetPosition() - this->GetPosition()).Length();
			if (distance < closestDistance)
			{
				closestDistance = distance;
				closestBase = base;
			}
		}
		object = object->GetNextActiveGameObject();
	}
	return closestBase;
}