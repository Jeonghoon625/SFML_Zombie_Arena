#include "Bullet.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Utils.h"
#include "../Utils/InputMgr.h"

Bullet::Bullet(Vector2i mouseDir, float dgree, Vector2f playerPosition) : texFileName("graphics/bullet.png"), dir(mouseDir), speed(1.f)
{
	this->dgree = dgree + 90;

	sprite.setTexture(TextureHolder::GetTexture(texFileName));
	Utils::SetOrigin(sprite, Pivots::CC);

	sprite.setRotation(this->dgree);

	position = playerPosition;
}

void Bullet::Update(float dt)
{
	position += dir * speed * dt;
	sprite.setPosition(position);
}

Sprite Bullet::GetSprite()
{
	return sprite;
}
