#pragma once
#include "Play.h"

class GameStateManager;

// All game object types inherit from game object base class
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	Play::Point2D GetPosition() const;

	void SetPosition(Play::Point2D const& newPosition);

	// call to schedule the object for deletion.
	void ScheduleDelete();

	GameObject* GetNextActiveGameObject() const;

protected:
	friend class GameStateManager;

	// This is executed by the game state manager once per frame. Override in subclass.
	virtual void Simulate(float elapsedTime);

	// This is executed by the game state manager once per frame, after simulate. Override in subclass.
	// pure virtual makes this class an abstract class!
	virtual void Draw() = 0; 

	Play::Point2D position;

	// set to true if the object should be deleted by the game state manager when time is right
	bool scheduledDelete;

	// All active game objects are in a linked list structure, managed by the game object manager.
	GameObject* nextActiveGameObject;
	// This will be set to the game state manager when the object is attached to it.
	GameStateManager* gameStateManager;
};