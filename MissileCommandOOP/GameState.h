#pragma once
#include "Play.h"
#include "constants.h"

class GameState
{
public:
	GameState();
	~GameState();

	void SetWorldSize(int width, int height);
	void NewGame();
	void ClearGame();
	void Update(float elapsedTime);

private:
	// Missiles
	std::vector<Play::Point2D> missile_origin;
	std::vector<Play::Point2D> missile_target;
	std::vector<Play::Point2D> missile_pos;
	std::vector<float> missile_distanceTravelled;
	std::vector<float> missile_speed;
	std::vector<Play::Colour> missile_colour;
	std::vector<bool> missile_isHostile;

	// Explosions
	std::vector<Play::Point2D> explosion_pos;
	std::vector<float> explosion_radius; // current visual radius
	std::vector<float> explosion_maxRadius; // used for scaling visuals
	std::vector<float> explosion_life; // remaining life
	std::vector<float> explosion_maxLife;

	// Cities
	std::vector<Play::Point2D> city_pos;
	std::vector<bool> city_alive;

	// Missile bases (Player)
	std::vector<Play::Point2D> base_pos;
	std::vector<int> base_missileCount;
	std::vector<int> base_maxMissiles;
	std::vector<float> base_timeSinceReload;
	std::vector<float> base_reloadTime;
	std::vector<bool> base_alive;
	std::vector<int> base_health;
	std::vector<float> base_missileSpeed;

	// Reticle
	Play::Point2D reticle_pos;
	bool mouseFired;

	// World and timing
	float timeSinceLastHostileMissile;
	float timeBetweenHostileMissiles;
	float hostileMissileSpeed;
	int worldWidth;
	int worldHeight;
	const float groundLevel = 16.0f;

	// Score
	int score;

	// System
	void SpawnHostileMissile();
	void RemoveMissile(size_t index);
	void SpawnExplosion(const Play::Point2D& pos);
	void RemoveExplosion(size_t index);
	void FireFromClosestBase(const Play::Point2D& target);
};