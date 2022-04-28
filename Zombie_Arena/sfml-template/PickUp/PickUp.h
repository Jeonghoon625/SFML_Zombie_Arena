#pragma once
#include <SFML/Graphics.hpp>
#include "../Wall/Wall.h"

using namespace sf;

enum class PickUpTypes
{
	Ammo,
	Health,
};
class PickUp
{
private:
	const int HEALTH_START_VALUE = 50;
	const int AMMO_START_VALUE = 12;
	const float START_WAIT_TIME = 1.f;
	const float START_SECONDS_FOR_LIVE = 10.f;

	PickUpTypes type;
	Sprite sprite;
	IntRect arena;
	std::vector<Wall*> walls;

	int value;

	bool spawned;
	float timer;

public:
	PickUp(PickUpTypes type);

	void Update(float dt);

	void Spawn(bool spawn);
	int GotIt();
	FloatRect GetGlobalBounds();
	PickUpTypes GetType();
	void SetArena(IntRect rect);
	bool IsSpawned();
	Sprite GetSprite();

	void Setwalls(std::vector<Wall*> vectorWalls);
};

