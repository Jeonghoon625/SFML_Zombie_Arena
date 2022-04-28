#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"

class TitleScene : public Scene
{
private:
	sf::Text textMessage;
	sf::Sprite spriteBackground;
	sf::Texture textureBackground;
	sf::Font font;

public:
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Draw(sf::RenderWindow* window);
};