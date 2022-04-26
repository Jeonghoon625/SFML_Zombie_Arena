#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;

	Vector2f position;

	std::string texFileName;
	Sprite sprite;

	Vector2i resolution;
	IntRect arena;

	int tileSize;

	Vector2f prevDirection;
	Vector2f direction;
	float prevSpeed;
	float speed;
	float acc;

	int health;
	int maxHealth;
	float immuneMs;

	Time lastHit;

public:
	Player();

	void Spawn(IntRect arena, Vector2i res, int tileSize);

	bool OnHitted(Time timeHit);

	Time GetLastTime() const;
	FloatRect GetGobalBound() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Sprite GetSprite() const;
	int GetHealth() const;

	void Update(float dt);

	void GetHealthItem(int amount);

	void UpgradeSpeed();
	void UpgradeMaxHealth();
};

