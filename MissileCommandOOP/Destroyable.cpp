#include "Destroyable.h"

Destroyable::Destroyable(int health) : health(health)
{
	// empty
}

int Destroyable::GetHealth() const
{
	return this->health;
}

void Destroyable::ReduceHealth(int amount)
{
	if (amount < 0)
		return;

	this->health -= amount;
}

bool Destroyable::IsDestroyed() const
{
	return health <= 0;
}
