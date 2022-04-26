#include "Wall.h"

Wall::Wall(int top, int left, int width, int height)
{
	wallRect.top = top;
	wallRect.left = left;
	wallRect.width = width;
	wallRect.height = height;
}

const FloatRect Wall::GetWallRect()
{
	return wallRect;
}