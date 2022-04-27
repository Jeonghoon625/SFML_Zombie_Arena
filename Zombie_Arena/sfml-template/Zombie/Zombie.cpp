#include "Zombie.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Utils.h"
#include <iostream>

std::vector<ZombieInfo> Zombie::zombieInfo;
bool Zombie::isInitInfo = false;

Zombie::Zombie()
{
	if (!isInitInfo)
	{
		zombieInfo.resize((int)ZombieTypes::COUNT);
		{
			auto& info = zombieInfo[(int)ZombieTypes::BLOATER];
			info.type = ZombieTypes::BLOATER;
			info.textureFileName = "graphics/bloater.png";
			info.speed = 40.f;
			info.health = 5;
		}
		{
			auto& info = zombieInfo[(int)ZombieTypes::CHASER];
			info.type = ZombieTypes::CHASER;
			info.textureFileName = "graphics/chaser.png";
			info.speed = 70.f;
			info.health = 1;
		}
		{
			auto& info = zombieInfo[(int)ZombieTypes::CRAWLER];
			info.type = ZombieTypes::CRAWLER;
			info.textureFileName = "graphics/crawler.png";
			info.speed = 20.f;
			info.health = 3;
			isInitInfo = true;
		}	
	}
}

bool Zombie::OnHitted()
{
	std::cout << "Hit" << std::endl;
	return false;
}

bool Zombie::IsALive()
{
	return alive;
}

void Zombie::Spawn(ZombieTypes type, IntRect arena, int x, int y, std::vector<Wall*> walls)
{
	auto& info = zombieInfo[(int)type];
	sprite.setTexture(TextureHolder::GetTexture(info.textureFileName));
	speed = info.speed;
	health = info.health;

	Utils::SetOrigin(sprite, Pivots::CC);
	FloatRect zombieBounds = sprite.getGlobalBounds();

	position.x = x;
	position.y = y;
	sprite.setPosition(position);

	//º®°ú °ãÄ¥½Ã ÁÂÇ¥ º¸Á¤
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
}

void Zombie::Update(float dt, Vector2f playerPosition)
{
	// ÀÌµ¿
	float h = playerPosition.x - position.x;
	float v = playerPosition.y - position.y;
	Vector2f dir(h, v);

	position += Utils::Normalize(dir) * speed * dt;
	sprite.setPosition(position);

	// È¸Àü
	float radian = atan2(dir.y, dir.x);
	float dgree = radian * 180.f / 3.141592;
	sprite.setRotation(dgree);
}

bool Zombie::UpdateCollision(Time time, Player& player)
{
	if (sprite.getGlobalBounds().intersects(player.GetGobalBound()))
	{
		return player.OnHitted(time);
	}
}

FloatRect Zombie::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

Sprite Zombie::GetSprite()
{
	return sprite;
}
