#include <cassert>
#include "GameStateManager.h"
#include "GameObject.h"
#include "City.h"
#include "MissileBase.h"
#include "Missile.h"
#include "Reticle.h"

GameStateManager::GameStateManager() : worldHeight(100), worldWidth(100)
{
	// reset game to initialized, but empty state.
	ClearGame();
}

GameStateManager::~GameStateManager()
{
	ClearGame();
}

void GameStateManager::Update(float elapsedTime)
{
	if (Play::KeyDown(Play::KEY_ENTER))
	{
		this->ClearGame();
		this->NewGame();
	}

	this->timeSinceLastHostileMissile += elapsedTime;
	// First, spawn incoming hostile missiles if necessary
	if (this->timeSinceLastHostileMissile >= this->timeBetweenHostileMissiles)
	{
		for (size_t i = 0; i < 1; i++)
		{
			Play::Point2D origin = Play::Point2D(Play::RandomRoll(this->worldWidth), this->worldHeight);
			Play::Point2D target = Play::Point2D(Play::RandomRoll(this->worldWidth), this->groundLevel);
			Missile* missile = new Missile(origin, target, Play::cRed, this->missileSpeed);
			this->AddGameObject(missile);
		}
		this->timeSinceLastHostileMissile = 0;
		this->timeBetweenHostileMissiles = std::fmaxf(0.005f, this->timeBetweenHostileMissiles - 0.035f);
		this->missileSpeed += 0.5f;
	}

	GameObject* object = this->gameObjects;
	
	// simulate all game objects
	while (object != nullptr)
	{
		if (object->scheduledDelete)
		{
			GameObject* next = object->nextActiveGameObject;
			this->RemoveGameObject(object);
			object = next;
			continue;
		}
		
		object->Simulate(elapsedTime);

		object = object->nextActiveGameObject;
	}

	// Draw a ground plane
	Play::DrawRect(Play::Point2D(0, 0), Play::Point2D(this->worldWidth, groundLevel), Play::cYellow, true);

	object = this->gameObjects;
	// Now draw the objects
	while (object != nullptr)
	{
		object->Draw();
		object = object->nextActiveGameObject;
	}
}

GameObject* GameStateManager::GetFirstGameObject()
{
	return gameObjects;
}

void GameStateManager::SetWorldSize(int width, int height)
{
	this->worldWidth = width;
	this->worldHeight = height;
}

void GameStateManager::AddGameObject(GameObject* gameObject)
{
	if (this->gameObjects == nullptr)
	{
		this->gameObjects = gameObject;
		gameObject->gameStateManager = this;
		return;
	}

	// Insert into front of linked list
	gameObject->nextActiveGameObject = this->gameObjects;
	this->gameObjects = gameObject;

	gameObject->gameStateManager = this;
}

bool GameStateManager::RemoveGameObject(GameObject* gameObject)
{
	// cannot remove a null object
	if (gameObject == nullptr)
	{
		return false;
	}

	GameObject* previousObject = nullptr;
	GameObject* object = this->gameObjects;
	while (object != nullptr)
	{
		if (object == gameObject)
		{
			if (previousObject == nullptr)
			{
				this->gameObjects = object->nextActiveGameObject;
			}
			else
			{
				previousObject->nextActiveGameObject = object->nextActiveGameObject;
			}
			delete gameObject;
			return true;
		}

		previousObject = object;
		object = object->nextActiveGameObject;
	}

	// could not find the object
	return false;
}

void GameStateManager::ClearGame()
{
	while (this->gameObjects != nullptr)
	{
		GameObject* object = this->gameObjects;
		this->gameObjects = object->nextActiveGameObject;
		delete object;
	}

	this->timeSinceLastHostileMissile = 0;
	this->timeBetweenHostileMissiles = 3.0f;
	this->missileSpeed = 10.0f;
}

void GameStateManager::NewGame()
{
	Reticle* reticle = new Reticle();
	reticle->SetPosition(Play::Input::GetMousePos());
	this->AddGameObject(reticle);

	for (size_t i = 0; i < 6; i++)
	{
		int offset = this->worldWidth / 7;
		City* city = new City();
		city->SetPosition(Play::Point2D(float(i) * offset + offset, groundLevel));
		this->AddGameObject(city);
	}

	for (size_t i = 0; i < 3; i++)
	{
		float offset = ((float)this->worldWidth / 7.0f);
		MissileBase* base = new MissileBase();
		base->SetPosition(Play::Point2D((offset * i * 2.0f) + offset * 1.4f, groundLevel));
		this->AddGameObject(base);
	}
}