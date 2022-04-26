#include "Player.h"
#include "../Utils/Utils.h"
#include "../Utils/InputMgr.h"
#include <cmath>
#include "../Utils/TextureHolder.h"

Player::Player()
	: speed(START_SPEED), acc(200.f), health(START_HEALTH), maxHealth(START_HEALTH),
	arena(), resolution(), tileSize(0.f), immuneMs(START_IMMUNE_MS), prevSpeed(0.f),
	texFileName("graphics/player.png")
{
	sprite.setTexture(TextureHolder::GetTexture(texFileName));

	Utils::SetOrigin(sprite, Pivots::CC);
}

void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{
	this->arena = arena;
	resolution = res;
	this->tileSize = tileSize;

	position.x = arena.width * 0.5f;
	position.y = arena.height * 0.5f;
}

bool Player::OnHitted(Time timeHit)
{
	if (lastHit.asMicroseconds() - lastHit.asMicroseconds() > immuneMs)
	{
		lastHit = timeHit;
		health -= 10;
		return true;
	}

	return false;
}

Time Player::GetLastTime() const
{
	return lastHit;
}

FloatRect Player::GetGobalBound() const
{
	return sprite.getGlobalBounds();
}

Vector2f Player::GetPosition() const
{
	return position;
}

float Player::GetRotation() const
{
	return sprite.getRotation();
}

Sprite Player::GetSprite() const
{
	return sprite;
}

int Player::GetHealth() const
{
	return health;
}

void Player::Update(float dt)
{
	// 사용자 입력
	float h = InputMgr::GetAxis(Axis::Horizontal);
	float v= InputMgr::GetAxis(Axis::Vertical);
	Vector2f dir(h, v);

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 1)
	{
		dir /= length;
	}

	position += dir * speed * dt;
	sprite.setPosition(position);

	// 회전
	Vector2i mousePos = InputMgr::GetMousePosition();
	Vector2i mouseDir;
	mouseDir.x = mousePos.x - resolution.x * 0.5f;
	mouseDir.y = mousePos.y - resolution.y * 0.5f;

	float radian = atan2(mouseDir.y, mouseDir.x);
	float dgree = radian * 180.f / 3.141592;
	sprite.setRotation(dgree);
}

void Player::GetHealthItem(int amount)
{
	health += amount;
	if (health > maxHealth)
	{
		health = maxHealth;
	}
	if (health < 0)
	{
		health = 0;
	}
}

void Player::UpgradeSpeed()
{
	speed += START_SPEED * 0.2f;
}

void Player::UpgradeMaxHealth()
{
	maxHealth += START_HEALTH * 0.2f;
}
