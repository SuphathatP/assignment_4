#include "GameState.h"

GameState::GameState()
{
	ClearGame();
}

GameState::~GameState()
{
	ClearGame();
}

void GameState::SetWorldSize(int width, int height)
{
	worldWidth = width;
	worldHeight = height;
}

void GameState::NewGame()
{
	ClearGame();

	// Reset timing and difficulty
	timeSinceLastHostileMissile = 0.0f;
	timeBetweenHostileMissiles = HOSTILE_SPAWN_INTERVAL_INIT;
	hostileMissileSpeed = HOSTILE_MISSILE_SPEED_INIT;
	mouseFired = false;
	score = 0;

	// Create reticle at mouse position
	reticle_pos = Play::Input::GetMousePos();

	// Create cities (6)
	city_pos.clear();
	city_alive.clear();
	int numCities = 6;
	int offset = worldWidth / (numCities + 1);
	for (int i = 0; i < numCities; ++i)
	{
		city_pos.push_back(Play::Point2D(float(i + 1) * offset, groundLevel));
		city_alive.push_back(true);
	}

	// Initialize missile bases (3)
	base_pos.clear();
	base_missileCount.clear();
	base_maxMissiles.clear();
	base_timeSinceReload.clear();
	base_reloadTime.clear();
	base_alive.clear();
	base_health.clear();
	base_missileSpeed.clear();

	int numBases = 3;
	for (int i = 0; i < numBases; ++i)
	{
		float offsetF = ((float)worldWidth / 7.0f);
		base_pos.push_back(Play::Point2D((offsetF * i * 2.0f) + offsetF * 1.4f, groundLevel));
		base_maxMissiles.push_back(BASE_MAX_MISSILES);
		base_missileCount.push_back(BASE_MAX_MISSILES);
		base_timeSinceReload.push_back(0.0f);
		base_reloadTime.push_back(BASE_RELOAD_TIME);
		base_alive.push_back(true);
		base_health.push_back(BASE_HEALTH);
		base_missileSpeed.push_back(BASE_MISSILE_SPEED);
	}

	// Pre-allocate memory
	missile_origin.reserve(64);
	missile_target.reserve(64);
	missile_pos.reserve(64);
	missile_distanceTravelled.reserve(64);
	missile_speed.reserve(64);
	missile_colour.reserve(64);
	missile_isHostile.reserve(64);

	explosion_pos.reserve(32);
	explosion_radius.reserve(32);
	explosion_maxRadius.reserve(32);
	explosion_life.reserve(32);
	explosion_maxLife.reserve(32);

	city_pos.shrink_to_fit(); // Keep cities compact

	// Clear missiles and explosions
	missile_origin.clear();
	missile_target.clear();
	missile_pos.clear();
	missile_distanceTravelled.clear();
	missile_speed.clear();
	missile_colour.clear();
	missile_isHostile.clear();

	explosion_pos.clear();
	explosion_radius.clear();
	explosion_maxRadius.clear();
	explosion_life.clear();
	explosion_maxLife.clear();
}

void GameState::ClearGame()
{
	missile_origin.clear();
	missile_target.clear();
	missile_pos.clear();
	missile_distanceTravelled.clear();
	missile_speed.clear();
	missile_colour.clear();
	missile_isHostile.clear();

	explosion_pos.clear();
	explosion_radius.clear();
	explosion_maxRadius.clear();
	explosion_life.clear();
	explosion_maxLife.clear();

	city_pos.clear();
	city_alive.clear();

	base_pos.clear();
	base_missileCount.clear();
	base_maxMissiles.clear();
	base_timeSinceReload.clear();
	base_reloadTime.clear();
	base_alive.clear();
	base_health.clear();
	base_missileSpeed.clear();

	timeSinceLastHostileMissile = 0.0f;
	timeBetweenHostileMissiles = HOSTILE_SPAWN_INTERVAL_INIT;
	hostileMissileSpeed = HOSTILE_MISSILE_SPEED_INIT;
	worldWidth = DISPLAY_WIDTH;
	worldHeight = DISPLAY_HEIGHT;
	mouseFired = false;
	score = 0;
}

// Spawn a single hostile missile with randomized origin and target
void GameState::SpawnHostileMissile()
{
	Play::Point2D origin(Play::RandomRoll(worldWidth), (float)worldHeight);
	Play::Point2D target((float)Play::RandomRoll(worldWidth), groundLevel);

	missile_origin.push_back(origin);
	missile_target.push_back(target);
	missile_pos.push_back(origin);
	missile_distanceTravelled.push_back(0.0f);

	// Make hostile missile speed slightly varied for gameplay feel
	float variation = ((Play::RandomRoll(100) / 100.0f) - 0.5f) * MISSILE_SPEED_VARIATION_SCALE;
	missile_speed.push_back(hostileMissileSpeed + variation);
	missile_colour.push_back(Play::cRed);
	missile_isHostile.push_back(true);

	// Audio
	Play::PlayAudio("Enemies");
}

void GameState::SpawnExplosion(const Play::Point2D& pos)
{
	explosion_pos.push_back(pos);
	explosion_radius.push_back(0.0f);
	explosion_maxRadius.push_back(EXPLOSION_MAX_RADIUS);
	explosion_life.push_back(EXPLOSION_MAX_LIFE);
	explosion_maxLife.push_back(EXPLOSION_MAX_LIFE);

	// Audio
	Play::PlayAudio("Explosion");
}

void GameState::RemoveMissile(size_t index)
{
	// Spawn explosion
	bool wasHostile = missile_isHostile[index];

	size_t last = missile_origin.size() - 1;
	if (index != last)
	{
		missile_origin[index] = missile_origin[last];
		missile_target[index] = missile_target[last];
		missile_pos[index] = missile_pos[last];
		missile_distanceTravelled[index] = missile_distanceTravelled[last];
		missile_speed[index] = missile_speed[last];
		missile_colour[index] = missile_colour[last];
		missile_isHostile[index] = missile_isHostile[last];
	}
	missile_origin.pop_back();
	missile_target.pop_back();
	missile_pos.pop_back();
	missile_distanceTravelled.pop_back();
	missile_speed.pop_back();
	missile_colour.pop_back();
	missile_isHostile.pop_back();
}

void GameState::RemoveExplosion(size_t index)
{
	size_t last = explosion_pos.size() - 1;
	if (index != last)
	{
		explosion_pos[index] = explosion_pos[last];
		explosion_radius[index] = explosion_radius[last];
		explosion_maxRadius[index] = explosion_maxRadius[last];
		explosion_life[index] = explosion_life[last];
		explosion_maxLife[index] = explosion_maxLife[last];
	}
	explosion_pos.pop_back();
	explosion_radius.pop_back();
	explosion_maxRadius.pop_back();
	explosion_life.pop_back();
	explosion_maxLife.pop_back();
}

void GameState::FireFromClosestBase(const Play::Point2D& target)
{
	// Find closest alive base with missiles
	int bestIndex = -1;
	float bestDistance = 1e9f;
	for (size_t i = 0; i < base_pos.size(); ++i)
	{
		if (!base_alive[i]) continue;
		if (base_missileCount[i] <= 0) continue;
		float distance_to_target = (base_pos[i] - target).Length();
		if (distance_to_target < bestDistance)
		{
			bestDistance = distance_to_target;
			bestIndex = (int)i;
		}
	}
	if (bestIndex == -1) return;

	// Spawn a player missile from base to target
	missile_origin.push_back(base_pos[bestIndex]);
	missile_target.push_back(target);
	missile_pos.push_back(base_pos[bestIndex]);
	missile_distanceTravelled.push_back(0.0f);
	missile_speed.push_back(base_missileSpeed[bestIndex]);
	missile_colour.push_back(Play::cBlue);
	missile_isHostile.push_back(false);

	base_missileCount[bestIndex] -= 1;

	// Audio
	Play::PlayAudio("Missile");
}

void GameState::Update(float elapsedTime)
{
	if (Play::KeyPressed(Play::KEY_ENTER))
	{
		Play::StopAudio("Music");
		this->ClearGame();
		this->NewGame();

		// Audio
		Play::PlayAudio("Start");
		Play::StartAudioLoop("Music");
	}

	// Spawn logic
	timeSinceLastHostileMissile += elapsedTime;
	if (timeSinceLastHostileMissile >= timeBetweenHostileMissiles)
	{
		SpawnHostileMissile();
		timeSinceLastHostileMissile = 0.0f;
		timeBetweenHostileMissiles = std::fmaxf(HOSTILE_SPAWN_MIN, timeBetweenHostileMissiles - HOSTILE_SPAWN_DECREASE);
		hostileMissileSpeed += HOSTILE_SPEED_RAMP_PER_SPAWN;
	}

	// Base reloads
	for (size_t b = 0; b < base_pos.size(); ++b)
	{
		if (!base_alive[b]) continue;
		if (base_missileCount[b] < base_maxMissiles[b])
		{
			base_timeSinceReload[b] += elapsedTime;
			if (base_timeSinceReload[b] >= base_reloadTime[b])
			{
				base_missileCount[b]++;
				base_timeSinceReload[b] = 0.0f;
			}
		}
	}

	// Input
	if (Play::Input::GetMouseDown(Play::Input::MouseButton::BUTTON_LEFT) && !mouseFired)
	{
		mouseFired = true;
		Play::Point2D target = Play::Input::GetMousePos();
		FireFromClosestBase(target);
	}
	if (!Play::Input::GetMouseDown(Play::Input::MouseButton::BUTTON_LEFT))
	{
		mouseFired = false;
	}

	// Simulate missiles in batch
	for (size_t i = 0; i < missile_origin.size(); )
	{
		float speed = missile_speed[i];
		missile_distanceTravelled[i] += speed * elapsedTime;
		Play::Vector2D direction = (missile_target[i] - missile_origin[i]);
		direction.Normalize();
		missile_pos[i] = missile_origin[i] + direction * missile_distanceTravelled[i];

		// Spawn explosion and remove missile if it reach target.
		float totalDistance = (missile_target[i] - missile_origin[i]).Length();
		if (missile_distanceTravelled[i] >= totalDistance)
		{
			SpawnExplosion(missile_pos[i]);
			RemoveMissile(i);
		}
		else
		{
			++i;
		}
	}

	// Simulate explosions
	for (size_t i = 0; i < explosion_pos.size(); )
	{
		explosion_life[i] -= elapsedTime;
		float lifeFraction = 1.0f - (explosion_life[i] / explosion_maxLife[i]);
		explosion_radius[i] = explosion_maxRadius[i] * lifeFraction;

		// Apply damage to nearby cities and bases.
		if (explosion_life[i] < explosion_maxLife[i] && explosion_life[i] + elapsedTime >= explosion_maxLife[i])
		{
			// Apply damage to cities
			for (size_t c = 0; c < city_pos.size(); ++c)
			{
				if (!city_alive[c]) continue;
				float distance = (city_pos[c] - explosion_pos[i]).Length();
				if (distance <= explosion_maxRadius[i])
				{
					city_alive[c] = false; // City destroyed
					// Decrease score for destroying city
					score -= SCORE_CITY;

					// Audio
					Play::PlayAudio("Building");
				}
			}

			// Apply damage to bases
			for (size_t b = 0; b < base_pos.size(); ++b)
			{
				if (!base_alive[b]) continue;
				float distance = (base_pos[b] - explosion_pos[i]).Length();
				if (distance <= explosion_maxRadius[i])
				{
					base_health[b] -= BASE_DAMAGE;
					if (base_health[b] <= 0)
					{
						base_alive[b] = false;
						// Decrease score for destroying base
						score -= SCORE_BASE;

						// Audio
						Play::PlayAudio("Building");
					}
				}
			}

			// Award points for destroying hostile missiles
			for (size_t m = 0; m < missile_origin.size(); )
			{
				if (!missile_isHostile[m]) { ++m; continue; }
				float distance = (missile_pos[m] - explosion_pos[i]).Length();
				if (distance <= explosion_maxRadius[i])
				{
					// Destroy missile and award score
					RemoveMissile(m);
					score += SCORE_MISSILE;
				}
				else { ++m; }
			}
		}

		if (explosion_life[i] <= 0.0f)
		{
			RemoveExplosion(i);
		}
		else
		{
			++i;
		}
	}

	// Drawing
	// Draw ground
	Play::DrawRect(Play::Point2D(0, 0), Play::Point2D((float)worldWidth, groundLevel), Play::cYellow, true);

	// Draw cities
	for (size_t c = 0; c < city_pos.size(); ++c)
	{
		if (city_alive[c])
		{
			Play::DrawSprite("city", city_pos[c], 0);
		}
		else
		{
			int spriteId = Play::GetSpriteId("rubble");
			if (spriteId >= 0)
			{
				Play::DrawSprite(spriteId, city_pos[c], 0);
			}
			else
			{
				// Safeguard
				Play::DrawSpriteTransparent("city", city_pos[c], 0, 1.0f, Play::cRed);
			}
		}
	}

	// Draw bases
	int baseSpriteId = Play::GetSpriteId("missile_base");
	int rubbleSpriteId = Play::GetSpriteId("rubble");
	for (size_t b = 0; b < base_pos.size(); ++b)
	{
		if (!base_alive[b])
		{
			if (rubbleSpriteId >= 0)
			{
				Play::DrawSprite(rubbleSpriteId, base_pos[b], 0);
			}
			else if (baseSpriteId >= 0)
			{
				// Safeguard
				Play::DrawSpriteTransparent(baseSpriteId, base_pos[b], 0, 1.0f, Play::cRed);
			}
			else
			{
				// Safeguard
				Play::DrawLine(base_pos[b] - Play::Point2D(8, 0), base_pos[b] + Play::Point2D(8, 12), Play::cRed);
			}
			continue;
		}

		if (baseSpriteId >= 0)
		{
			Play::DrawSprite(baseSpriteId, base_pos[b], 0);

			// Place missile count relative to sprite origin so it appears near the base
			Play::Point2D origin = Play::GetSpriteOrigin(baseSpriteId);
			Play::DrawDebugText(base_pos[b] + Play::Vector2f(origin.x + 6, -8), std::to_string(base_missileCount[b]).c_str(), Play::cBlack);

			// Draw base health
			/* std::string healthText = std::string("HP:") + std::to_string(base_health[b]);
			Play::DrawDebugText(base_pos[b] + Play::Vector2f(origin.x + 6, + 100), healthText.c_str(), Play::cWhite); */
		}
		else
		{
			Play::DrawRect(base_pos[b] - Play::Point2D(6, 0), base_pos[b] + Play::Point2D(6, 10), Play::cWhite, true);

			// Draw missile count
			Play::DrawDebugText(base_pos[b] + Play::Vector2f(6, -8), std::to_string(base_missileCount[b]).c_str(), Play::cBlack);

			// Draw base health (Safeguard)
			/* std::string healthText = std::string("HP:") + std::to_string(base_health[b]);
			Play::DrawDebugText(base_pos[b] + Play::Vector2f(6, -20), healthText.c_str(), Play::cWhite); */
		}
	}

	// Draw missiles
	for (size_t i = 0; i < missile_origin.size(); ++i)
	{
		Play::Vector2D direction = missile_target[i] - missile_origin[i];
		direction.Normalize();
		Play::Point2D endPoint = missile_origin[i] + direction * missile_distanceTravelled[i];
		Play::DrawLine(missile_origin[i], endPoint, missile_colour[i]);
		Play::DrawPixel(endPoint, Play::cWhite);
		Play::DrawCircle(missile_target[i], 2, missile_colour[i]);
	}

	// Draw explosions
	for (size_t i = 0; i < explosion_pos.size(); ++i)
	{
		Play::DrawCircle(explosion_pos[i], (int)explosion_radius[i], Play::cOrange);
	}

	// Draw reticle
	reticle_pos = Play::Input::GetMousePos();
	Play::DrawCircle(reticle_pos, 2, Play::cWhite);

	// HUD 
	// Draw score
	Play::DrawDebugText(Play::Point2D(22, (float)worldHeight - 127), std::to_string(score).c_str(), Play::cBlack);
}