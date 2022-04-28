#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Blood
{
private:
	const float LIFE_TIME = 1.f;

	bool isActive;

	Vector2f position;
	Sprite sprite;

	std::string textureFileName;

	float timer;

public:
	Blood();

	void SetActive(bool active);
	void Update(float dt);
	bool IsActive();
	void Spawn(Vector2f pos);
	Sprite GetSprite();
};

