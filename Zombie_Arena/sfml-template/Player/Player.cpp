#include "Player.h"
#include "../Utils/Utils.h"
#include "../Utils/InputMgr.h"
#include <cmath>
#include <iostream>
#include "../Utils/TextureHolder.h"
#include <algorithm>
#include "../PickUp/PickUp.h"

Player::Player()
	: speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH),
	arena(), resolution(), tileSize(0.f), immuneMs(START_IMMUNE_MS), distanceToMuzzle(45.f),
	texFileName("graphics/player.png"), timer(SHOOT_DELAY)
{
	sprite.setTexture(TextureHolder::GetTexture(texFileName));
	Utils::SetOrigin(sprite, Pivots::CC);

	for (int i = 0; i < BULLET_CACHE_SIZE; ++i)
	{
		unuseBullets.push_back(new Bullet());
	}
}

Player::~Player()
{
	for (auto bullet : unuseBullets)
	{
		delete bullet;
	}
	unuseBullets.clear();

	for (auto bullet : useBullets)
	{
		delete bullet;
	}
	useBullets.clear();
}

void Player::Shoot(Vector2f dir)
{
	Vector2f spawnPos = position + dir * distanceToMuzzle;

	if (unuseBullets.empty())
	{
		for (int i = 0; i < BULLET_CACHE_SIZE; ++i)
		{
			unuseBullets.push_back(new Bullet());
		}
	}

	Bullet* bullet = unuseBullets.front();
	unuseBullets.pop_front();

	useBullets.push_back(bullet);
	bullet->Shoot(spawnPos, dir);
}

void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{
	this->arena = arena;
	resolution = res;
	this->tileSize = tileSize;

	position.x = arena.width * 0.5f;
	position.y = arena.height * 0.5f;
	sprite.setPosition(position.x, position.y);
}

bool Player::OnHitted(Time timeHit)
{
	if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > immuneMs)
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

bool Player::UpdateCollision(const std::vector<Zombie*>& zombies)
{
	bool isCollided = false;
	for (auto bullet : useBullets)
	{

		if (bullet->UpdateCollision(zombies))
		{
			isCollided = true;
		};
	}
	return isCollided;
}

bool Player::UpdateCollision(const std::vector<PickUp*>& items)
{
	FloatRect bounds = sprite.getGlobalBounds();
	bool isCollided = false;
	for (auto item : items)
	{

		if (bounds.intersects(item->GetGlobalBounds()))
		{
			item->GotIt();
			isCollided = true;
		};	
	}
	return isCollided;
}

void Player::Update(float dt, std::vector <Wall*> walls)
{
	// 이동
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


	//충돌
	for (auto v : walls)
	{
		if (sprite.getGlobalBounds().intersects(v->GetWallRect()))
		{

			Pivots pivot = Utils::CollisionDir(v->GetWallRect(), sprite.getGlobalBounds());

			switch (pivot)
			{
			case Pivots::LC:
				position.x += (v->GetWallRect().left + v->GetWallRect().width) - (sprite.getGlobalBounds().left);
				InputMgr::HorInit();
				break;

			case Pivots::RC:
				position.x -= (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) - (v->GetWallRect().left);
				InputMgr::HorInit();
				break;

			case Pivots::CT:
				position.y += (v->GetWallRect().top + v->GetWallRect().height) - (sprite.getGlobalBounds().top);
				InputMgr::VerInit();
				break;

			case Pivots::CB:
				position.y -= (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) - (v->GetWallRect().top);
				InputMgr::VerInit();
				break;

			defalut:
				break;
			}
			sprite.setPosition(position);
		}
	}

	// 회전
	Vector2i mousePos = InputMgr::GetMousePosition();
	Vector2i mouseDir;
	mouseDir.x = mousePos.x - resolution.x * 0.5f;
	mouseDir.y = mousePos.y - resolution.y * 0.5f;
	float radian = atan2(mouseDir.y, mouseDir.x);
	float dgree = radian * 180.f / 3.141592;
	sprite.setRotation(dgree);

	timer -= dt;
	if (InputMgr::GetMouseButton(Mouse::Button::Left))
	{
		if (timer < 0)
		{
			Shoot(Utils::Normalize(Vector2f(mouseDir.x, mouseDir.y)));
			timer = SHOOT_DELAY;
		}
	}

	auto it = useBullets.begin();
	while (it != useBullets.end())
	{
		Bullet* bullet = *it;
		bullet->Update(dt);

		if (!bullet->IsActive())
		{
			it = useBullets.erase(it);
			unuseBullets.push_back(bullet);

		}
		else
		{
			++it;
		}
	}
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
	for (auto bullet : useBullets)
	{
		window.draw(bullet->GetShape());
	}

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
