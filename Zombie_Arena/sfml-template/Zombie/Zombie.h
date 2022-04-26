#pragma once
#include <SFML/Graphics.hpp>
#include "../Wall/Wall.h"

using namespace sf;

enum class ZombieTypes
{
	BLOATER,
	CHASER,
	CRAWLER,
	COUNT,
};

struct ZombieInfo
{
	ZombieTypes type;
	std::string textureFileName;
	float speed;
	int health;
};

class Zombie
{
private:
	const float BLOATER_SPEED = 40;
	Vector2f position;
	Sprite sprite;

	float speed;
	int health;

	static std::vector<ZombieInfo> zombieInfo;
	static bool isInitInfo;
	bool alive;

public:
	Zombie();

	bool OnHitted();
	bool IsALive();

	void Spawn(ZombieTypes type, IntRect arena, int x, int y, std::vector<Wall*> walls);
	void Update(float dt, Vector2f playerPosition);

	FloatRect GetGlobalBound();
	Sprite GetSprite();

};

