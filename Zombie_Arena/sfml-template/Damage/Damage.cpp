#include "Damage.h"
#include "../Utils/Utils.h"

Damage::Damage()
	: speed(MASSAGE_SPEED), isActive(false)
{
	fontZombiecontrol.loadFromFile("fonts/zombiecontrol.ttf");
	textDamage.setFont(fontZombiecontrol);
	textDamage.setString("-5");
	textDamage.setFillColor(Color::Red);
	textDamage.setCharacterSize(20);

	Utils::SetOrigin(textDamage, Pivots::CC);
}

void Damage::SetActive(bool active)
{
	isActive = active;
}

bool Damage::IsActive()
{
	return isActive;
}

void Damage::HitPlayer(Vector2f pos)
{
	SetActive(true);

	distance = 0.f;
	postion = pos;
	textDamage.setPosition(postion);
}

void Damage::Stop()
{
	SetActive(false);
}

void Damage::Update(float dt)
{
	postion.y -= speed * dt;
	textDamage.setPosition(postion);

	distance += speed * dt;
	if (distance > DEFAULT_DISTANCE)
	{
		Stop();
	}
}

Text Damage::GetText()
{
	return textDamage;
}
