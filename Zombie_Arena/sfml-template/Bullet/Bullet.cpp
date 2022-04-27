#include "Bullet.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Utils.h"
#include "../Utils/InputMgr.h"
#include "../Zombie/Zombie.h"

Bullet::Bullet() : speed(DEFAULT_SPEED), isActive(false), textureFileName("graphics/bullet.png")
{
	shape.setTexture(&TextureHolder::GetTexture(textureFileName));
	shape.setSize(Vector2f(30, 15));
	Utils::SetOrigin(shape, Pivots::CC);
}

void Bullet::SetActive(bool active)
{
	isActive = active;
}  

void Bullet::Shoot(Vector2f pos, Vector2f dir)
{
	SetActive(true);

	distance = 0.f;
	position = pos;
	direction = Utils::Normalize(dir);
	float degree = Utils::GetAngel(position, position + direction);
	shape.setRotation(degree);
	shape.setPosition(position);
}

bool Bullet::IsActive()
{
	return isActive;
}

bool Bullet::UpdateCollision(const std::vector<Zombie*>& zombies)
{
	FloatRect bounds = shape.getGlobalBounds();

	for (auto zombie : zombies)
	{
		if (zombie->IsALive())
		{
			if (bounds.intersects(zombie->GetGlobalBound()))
			{
				zombie->OnHitted();
				Stop();

				return true;
			}
		}
	}

	return false;
}

Sprite Bullet::GetSprite()
{
	return sprite;
}

RectangleShape Bullet::GetShape()
{
	return shape;
}

void Bullet::Update(float dt)
{
	position += direction * speed * dt;
	shape.setPosition(position);

	distance += speed * dt;

	if (distance > DEFAULT_DISTANCE)
	{
		Stop();
	}
}

void Bullet::Stop()
{
	SetActive(false);
}
