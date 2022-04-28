#include "PickUp.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Utils.h"
#include <iostream>

PickUp::PickUp(PickUpTypes type) : type(type)
{
	std::string textureId;
	switch (this->type)
	{
	case PickUpTypes::Health:
		textureId = "graphics/health_pickup.png";
		value = AMMO_START_VALUE;
		break;

	case PickUpTypes::Ammo:
		textureId = "graphics/ammo_pickup.png";
		value = HEALTH_START_VALUE;
		break;
	}

	sprite.setTexture(TextureHolder::GetTexture(textureId));
	Utils::SetOrigin(sprite, Pivots::CC);

	Spawn(false);
	timer = START_WAIT_TIME;
}

void PickUp::Update(float dt)
{
	timer -= dt;
	if (timer < 0.f)
	{
		Spawn(!spawned);
	}
}

void PickUp::Spawn(bool spawn)
{
	spawned = spawn;
	if (spawned)
	{
		timer = START_SECONDS_FOR_LIVE;

		int offset = 50;
		int minX = arena.left + offset;
		int maxX = arena.width - offset;
		int minY = arena.top + offset;
		int maxY = arena.height - offset;

		int x = Utils::RandomRange(minX, maxX + 1);
		int y = Utils::RandomRange(minY, maxY + 1);

		Vector2f position;

		position.x = x;
		position.y = y;
		sprite.setPosition(position);

		for (auto v : walls)
		{
			if (sprite.getGlobalBounds().intersects(v->GetWallRect()))
			{
				Pivots pivot = Utils::CollisionDir(v->GetWallRect(), sprite.getGlobalBounds());

				switch (pivot)
				{
				case Pivots::LC:
					position.x += (v->GetWallRect().left + v->GetWallRect().width) - (sprite.getGlobalBounds().left);
					break;

				case Pivots::RC:
					position.x -= (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) - (v->GetWallRect().left);
					break;

				case Pivots::CT:
					position.y += (v->GetWallRect().top + v->GetWallRect().height) - (sprite.getGlobalBounds().top);
					break;

				case Pivots::CB:
					position.y -= (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) - (v->GetWallRect().top);
					break;

				defalut:
					break;
				}
				sprite.setPosition(position);
			}
		}

		//sprite.setPosition(Vector2f(x, y));
	}
	else
	{
		timer = START_WAIT_TIME;
	}
}

int PickUp::GotIt()
{
	switch (type)
	{
	case PickUpTypes::Ammo:
		Spawn(false);
		break;
	case PickUpTypes::Health:
		Spawn(false);
		break;
	}
	return value;
}

FloatRect PickUp::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

PickUpTypes PickUp::GetType()
{
	return type;
}

void PickUp::SetArena(IntRect rect)
{
	arena = rect;
}

bool PickUp::IsSpawned()
{
	return spawned;
}

Sprite PickUp::GetSprite()
{
	return sprite;
}

void PickUp::Setwalls(std::vector<Wall*> vectorWalls)
{
	walls = vectorWalls;
}

