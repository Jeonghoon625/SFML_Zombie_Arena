#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Damage
{
private:
	Font fontZombiecontrol;
	const float MASSAGE_SPEED = 50.f;
	const float DEFAULT_DISTANCE = 50.f;

	bool isActive;

	Text textDamage;

	Vector2f postion;
	float speed;
	float distance;

public:
	Damage();

	void SetActive(bool active);
	bool IsActive();
	void HitPlayer(Vector2f pos);
	void Stop();

	void Update(float dt);
	Text GetText();
};

