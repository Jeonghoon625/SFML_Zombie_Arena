#include "TitleScene.h"

void TitleScene::Init()
{
}

void TitleScene::Update(float deltaTime)
{
}

void TitleScene::Draw(sf::RenderWindow* window)
{
	window->draw(spriteBackground);
	window->draw(textMessage);
}

TitleScene::~TitleScene()
{
}