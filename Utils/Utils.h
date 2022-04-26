#pragma once
#include <SFML/Graphics.hpp>
#include <random>

using namespace sf;

enum class Pivots
{
	// L, CH, R
	// T, CV, R
	LT, CT, RT,
	LC, CC, RC,
	LB, CB, RB
};

class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static void SetOrigin(Text& text, Pivots preset);

	static void SetOrigin(Sprite& sprite, Pivots preset);

	static void SetOrigin(Shape& shape, Pivots preset);

	static void SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset);

	static int RandomRange(int min, int excludeMax);
};

