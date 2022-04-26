#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
private :
	Sprite sprite;
	std::string texFileName;
	Vector2f dir;
	float dgree;
	float speed;
	Vector2f position;

public :
	Bullet(Vector2i mouseDir, float dgree, Vector2f playerPosition);
	void Update(float dt);
	Sprite GetSprite();
};

