#include "Blood.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Utils.h"

Blood::Blood() : isActive(false), textureFileName("graphics/blood.png"), timer(LIFE_TIME)
{
	sprite.setTexture(TextureHolder::GetTexture(textureFileName));
	Utils::SetOrigin(sprite, Pivots::CC);
}

void Blood::SetActive(bool active)
{
	isActive = active;
}

void Blood::Spawn(Vector2f pos)
{
	SetActive(true);

	position = pos;
	sprite.setPosition(position);
}

bool Blood::IsActive()
{
	return isActive;
}

Sprite Blood::GetSprite()
{
	return sprite;
}


void Blood::Update(float dt)
{
	timer -= dt;
	if (timer < 0)
	{
		SetActive(false);
	}
}