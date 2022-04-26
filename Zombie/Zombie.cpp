#include "Zombie.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Utils.h"

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
	return false;
}

bool Zombie::IsALive()
{
	return alive;
}

void Zombie::Spawn(ZombieTypes type, IntRect arena)
{
	auto& info = zombieInfo[(int)type];
	sprite.setTexture(TextureHolder::GetTexture(info.textureFileName));
	speed = info.speed;
	health = info.health;

	Utils::SetOrigin(sprite, Pivots::CC);
	FloatRect zombieBounds = sprite.getGlobalBounds();

	int offset_hori = zombieBounds.width * 0.5 + 50; 
	int offset_verti = zombieBounds.height * 0.5 + 50;

	int minX = arena.left + offset_hori;
	int maxX = arena.width - offset_hori;
	int minY = arena.top + offset_verti;
	int maxY = arena.height - offset_verti;

	int x = Utils::RandomRange(minX, maxX + 1);
	int y = Utils::RandomRange(minY, maxY + 1);

	position.x = x;
	position.y = y;
	
	
	sprite.setPosition(position);
}

void Zombie::Update(float dt, Vector2f playerPosition)
{
	// 이동
	float h = playerPosition.x - position.x;
	float v = playerPosition.y - position.y;
	Vector2f dir(h, v);

	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length > 0)
	{
		dir /= length;
	}

	position += dir * speed * dt;
	sprite.setPosition(position);

	// 회전
	float radian = atan2(dir.y, dir.x);
	float dgree = radian * 180.f / 3.141592;
	sprite.setRotation(dgree);
}

FloatRect Zombie::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

Sprite Zombie::GetSprite()
{
	return sprite;
}
