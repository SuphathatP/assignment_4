#pragma once
#include "GameObject.h"

class Destroyable : public GameObject
{
public:
	Destroyable(int health);

	int GetHealth() const;
	
	// call to reduce the health of the object.
	void ReduceHealth(int amount);

	// Check if the object is destroyed
	bool IsDestroyed() const;

private:
	int health;
};

