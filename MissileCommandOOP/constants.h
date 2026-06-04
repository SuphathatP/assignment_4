#pragma once

// Display
constexpr int DISPLAY_WIDTH = 240;
constexpr int DISPLAY_HEIGHT = 135;
constexpr int DISPLAY_SCALE = 4;

constexpr float GROUND_LEVEL = 16.0f;

// Gameplay
constexpr float HOSTILE_SPAWN_INTERVAL_INIT = 3.0f; // Seconds between hostile missiles at start
constexpr float HOSTILE_SPAWN_DECREASE = 0.035f; // Decrease in spawn interval per spawn
constexpr float HOSTILE_SPAWN_MIN = 0.005f; // Minimum interval between spawns
constexpr float HOSTILE_MISSILE_SPEED_INIT = 10.0f; // Starting speed for hostile missiles
constexpr float HOSTILE_SPEED_RAMP_PER_SPAWN = 1.0f; // Speed increase per spawn

constexpr int BASE_MAX_MISSILES = 10;
constexpr float BASE_RELOAD_TIME = 1.0f;
constexpr int BASE_DAMAGE = 50;
constexpr int BASE_HEALTH = 100; // default health for bases

constexpr float BASE_MISSILE_SPEED = 40.0f;
constexpr float MISSILE_SPEED_VARIATION_SCALE = 2.0f; // Used when random variation

// Explosion
constexpr float EXPLOSION_MAX_RADIUS = 10.0f;
constexpr float EXPLOSION_MAX_LIFE = 0.8f;

// Score
constexpr int SCORE_CITY = 100;
constexpr int SCORE_BASE = 200;
constexpr int SCORE_MISSILE = 100;