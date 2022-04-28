#include "TitleScene.h"

void TitleScene::Init()
{
	//textureBackground = *ResourceManager::GetInstance().GetTexture("Background");
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);
	
	//UI
	//font = *ResourceManager::GetInstance().GetFont("KOMIKAP");
	textMessage.setFont(font);
	textMessage.setString("Press Enter to start!");
	textMessage.setCharacterSize(75);
	textMessage.setFillColor(sf::Color::White);

	sf::FloatRect textRect = textMessage.getLocalBounds();
	textMessage.setOrigin(
		textRect.left + textRect.width * 0.5f,
		textRect.top + textRect.height * 0.5f
	);
	textMessage.setPosition(1920 * 0.5f, 1080 * 0.5f);
}

void TitleScene::Update(float deltaTime)
{
}

void TitleScene::Draw(sf::RenderWindow* window)
{
	window->draw(spriteBackground);
	window->draw(textMessage);
}
