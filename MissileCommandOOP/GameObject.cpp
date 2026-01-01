#include "GameObject.h"

GameObject::GameObject() : nextActiveGameObject(nullptr), gameStateManager(nullptr), scheduledDelete(false)
{
}

GameObject::~GameObject()
{
	// override in subclass
}

Play::Point2D GameObject::GetPosition() const
{
	return this->position;
}

void GameObject::SetPosition(Play::Point2D const& newPosition)
{
	this->position = newPosition;
}

void GameObject::ScheduleDelete()
{
	this->scheduledDelete = true;
}

GameObject* GameObject::GetNextActiveGameObject() const
{
	return this->nextActiveGameObject;
}

void GameObject::Simulate(float elapsedTime)
{
	// override in subclass
}
