#include "TitleScene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include <iostream>
void TitleScene::Init(SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;
	fontKOMIKAP.loadFromFile("fonts/zombiecontrol.ttf");
	textureTitle = TextureHolder::GetTexture("graphics/background.png");
	spriteTitle.setTexture(textureTitle);
	spriteTitle.setPosition(0, 0);

	textTitle.setFont(fontKOMIKAP);
	textTitle.setString("Zombie Arena!");
	textTitle.setFillColor(Color::Red);
	textTitle.setCharacterSize(200);
	FloatRect TitleRect = textTitle.getLocalBounds();
	textTitle.setOrigin(
		TitleRect.left + TitleRect.width * 0.5f,
		TitleRect.top + TitleRect.height * 0.5f
	);
	textTitle.setPosition(TITLE_XPOS, 110);

	textMenu1.setFont(fontKOMIKAP);
	textMenu1.setString("GAME START");
	textMenu1.setFillColor(Color::White);
	textMenu1.setPosition(MENU_XPOS, MENU_YPOS);
	textMenu1.setCharacterSize(50);

	textMenu2.setFont(fontKOMIKAP);
	textMenu2.setString("GAME EXIT");
	textMenu2.setFillColor(Color::White);
	textMenu2.setPosition(MENU_XPOS, MENU_YPOS + 100);
	textMenu2.setCharacterSize(50);

	textMenu3.setFont(fontKOMIKAP);
	textMenu3.setString("HIGH SCORE");
	textMenu3.setFillColor(Color::White);
	textMenu3.setPosition(MENU_XPOS, MENU_YPOS + 50);
	textMenu3.setCharacterSize(50);

	textureCS = TextureHolder::GetTexture("graphics/CS.png");

	spriteCS.setTexture(textureCS);
	spriteCS.setPosition(MENU_XPOS - 80, MENU_YPOS);

	menuPos = 1;
}

void TitleScene::Update(Time dt, Time playTime, RenderWindow* window, View* mainView)
{
	if (InputMgr::GetKeyDown(Keyboard::Up) && menuPos > 1)
	{
		menuPos--;
		spriteCS.setPosition(MENU_XPOS - 80, spriteCS.getPosition().y - 50);
	}

	if (InputMgr::GetKeyDown(Keyboard::Down) && menuPos < 3)
	{
		menuPos++;
		spriteCS.setPosition(MENU_XPOS - 80, spriteCS.getPosition().y + 50);
	}

	if (InputMgr::GetKeyDown(Keyboard::Enter))
	{
		if (menuPos == 1)
		{
			sceneManager->sceneSwitch(SceneType::GAME);
		}
	}
}

void TitleScene::Draw(sf::RenderWindow* window, View* mainView, View* uiView)
{
	window->setView(*uiView);
	window->draw(spriteTitle);
	window->draw(textTitle);
	window->draw(textMenu1);
	window->draw(textMenu3);
	window->draw(textMenu2);
	window->draw(spriteCS);
}

TitleScene::~TitleScene()
{
}