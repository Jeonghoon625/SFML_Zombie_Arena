#include "Bullet.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Utils.h"
#include "../Utils/InputMgr.h"

Bullet::Bullet() : speed(DEFAULT_SPEED), isActive(false)
{
	shape.setSize(Vector2f(2, 2));
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
	shape.setPosition(position);
}

bool Bullet::IsActive()
{
	return isActive;
}

RectangleShape Bullet::GetShape()
{
	return RectangleShape();
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
