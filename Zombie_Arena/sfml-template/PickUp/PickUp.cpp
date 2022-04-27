#include "PickUp.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Utils.h"
PickUp::PickUp(PickUpTypes type) : type(type)
{
	std::string textureId;
	switch (this->type)
	{
	case PickUpTypes::Health:
		textureId = "graphics/ammo_pickup.png";
		value = AMMO_START_VALUE;
		break;

	case PickUpTypes::Ammo:
		textureId = "graphics/health_pickup.png";
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
}

void PickUp::Spawn(bool spawn)
{
	spawned = spawn;
	if (spawned)
	{
		timer = START_SECONDS_FOR_LIVE;
		int x = Utils::RandomRange(arena.left, arena.left + arena.width);
		int y = Utils::RandomRange(arena.top, arena.top + arena.height);

	}
	else
	{
		timer = START_WAIT_TIME;
	}
}

int PickUp::GotIt()
{
	return 0;
}

void PickUp::SetArena(IntRect rect)
{
}

bool PickUp::IsSpawned()
{
	return false;
}

Sprite PickUp::GetSprite()
{
	return Sprite();
}
