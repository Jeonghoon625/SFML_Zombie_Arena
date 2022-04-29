#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie;
class Wall;

class Bullet
{
private :
	const float DEFAULT_SPEED = 800.f;
	const float DEFAULT_DISTANCE = 1000.f;

	bool isActive;

	RectangleShape shape;

	Vector2f position;
	Vector2f direction;
	float speed;
	float distance;
	Sprite sprite;

	std::string textureFileName;

public :
	Bullet();

	void SetActive(bool active);
	void Shoot(Vector2f pos, Vector2f dir);
	void Update(float dt);
	void Stop();
	bool IsActive();
	bool UpdateCollision(const std::vector<Zombie*>& zombies);
	bool UpdateCollision(const std::vector<Wall*>& walls);
	Sprite GetSprite();
	RectangleShape GetShape();

	
};

