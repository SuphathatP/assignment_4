#pragma once

// Forward declarations
class GameObject;

// GameStateManager keeps track of the game state
class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void Update(float elapsedTime);
	
	GameObject* GetFirstGameObject();

	void SetWorldSize(int width, int height);

	// Add a game object to the game state. This makes the game object active and automatically updated.
	void AddGameObject(GameObject* gameObject);
	// Removes a game object from the list of active objects. This deletes the object, and returns true or false if it was successful or not.
	bool RemoveGameObject(GameObject* gameObject);

	// Starts a new game by instantiating all necessary objects.
	void NewGame();
	// Destorys all game objects and wipes the game clean.
	void ClearGame();

private:
	int worldWidth;
	int worldHeight;

	float timeSinceLastHostileMissile;
	float timeBetweenHostileMissiles;
	float missileSpeed;

	const float groundLevel = 16.0f;

	// linked list of game objects
	GameObject* gameObjects;
};

