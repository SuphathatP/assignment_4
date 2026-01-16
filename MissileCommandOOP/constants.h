#pragma once

// Display
const int DISPLAY_WIDTH = 240;
const int DISPLAY_HEIGHT = 135;
const int DISPLAY_SCALE = 4;

// Gameplay
const float HOSTILE_SPAWN_INTERVAL_INIT = 3.0f; // Seconds between hostile missiles at start
const float HOSTILE_SPAWN_DECREASE = 0.035f; // Decrease in spawn interval per spawn
const float HOSTILE_SPAWN_MIN = 0.005f; // Minimum interval between spawns
const float HOSTILE_MISSILE_SPEED_INIT = 10.0f; // Starting speed for hostile missiles
const float HOSTILE_SPEED_RAMP_PER_SPAWN = 1.0f; // Speed increase per spawn

const int BASE_MAX_MISSILES = 10;
const float BASE_RELOAD_TIME = 1.0f;
const float BASE_MISSILE_SPEED = 40.0f;
const int BASE_DAMAGE = 50;
const int BASE_HEALTH = 100; // default health for bases

const float MISSILE_SPEED_VARIATION_SCALE = 2.0f; // Used when random variation

// Explosion
const float EXPLOSION_MAX_RADIUS = 10.0f;
const float EXPLOSION_LIFE = 0.8f;

// Score
const int SCORE_CITY = 100;
const int SCORE_BASE = 200;
const int SCORE_MISSILE = 100;