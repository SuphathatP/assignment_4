#pragma once
constexpr int DISPLAY_WIDTH = 240;
constexpr int DISPLAY_HEIGHT = 160;
constexpr int DISPLAY_SCALE = 4;

constexpr float GROUND_Y = 16.0f;

constexpr unsigned int COUNT_BASES = 3u;
constexpr unsigned int COUNT_CITIES = 6u;
constexpr unsigned int COUNT_BUILDINGS = COUNT_BASES + COUNT_CITIES;

constexpr int BASE_MAX_MISSILES = 10;
constexpr float BASE_RELOAD_TIME = 1.0f;

constexpr int MISSILE_DAMAGE = 50;

// Explosion
constexpr float EXPLOSION_MAX_RADIUS = 10.0f;
constexpr float EXPLOSION_MAX_RADIUS_SQRD = EXPLOSION_MAX_RADIUS * EXPLOSION_MAX_RADIUS;
constexpr float EXPLOSION_MAX_LIFE = 0.8f;
//constexpr int BASE_HEALTH = 100;

// Score
//constexpr int SCORE_CITY = 100;
//constexpr int SCORE_BASE = 200;
//constexpr int SCORE_MISSILE = 100;