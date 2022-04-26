#include "Utils.h"

std::random_device Utils::rd;
std::mt19937 Utils::gen(rd());

void Utils::SetOrigin(sf::Text& text, Pivots preset)
{
	SetOrigin(text, text.getLocalBounds(), preset);
}

void Utils::SetOrigin(sf::Shape& shape, Pivots preset)
{
	SetOrigin(shape, shape.getLocalBounds(), preset);
}

void Utils::SetOrigin(sf::Sprite& sprite, Pivots preset)
{
	SetOrigin(sprite, sprite.getLocalBounds(), preset);
}

void Utils::SetOrigin(sf::Transformable& tr, sf::FloatRect bounds, Pivots preset)
{
	switch (preset)
	{
	case Pivots::LT:
		tr.setOrigin(bounds.left, bounds.top);
		break;
	case Pivots::LC:
		tr.setOrigin(bounds.left, bounds.height * 0.5f);
		break;
	case Pivots::LB:
		tr.setOrigin(bounds.left, bounds.height);
		break;

	case Pivots::CT:
		tr.setOrigin(bounds.width * 0.5f, bounds.top);
		break;
	case Pivots::CC:
		tr.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
		break;
	case Pivots::CB:
		tr.setOrigin(bounds.width * 0.5f, bounds.height);
		break;

	case Pivots::RT:
		tr.setOrigin(bounds.width, bounds.top);
		break;
	case Pivots::RC:
		tr.setOrigin(bounds.width, bounds.height * 0.5f);
		break;
	case Pivots::RB:
		tr.setOrigin(bounds.width, bounds.height);
		break;

	default:
		break;
	}
}

int Utils::RandomRange(int min, int excludeMax)
{
	int range = excludeMax - min;
	return min + gen() % range;
}