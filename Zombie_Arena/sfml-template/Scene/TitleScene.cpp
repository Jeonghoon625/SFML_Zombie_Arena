#include "TitleScene.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/InputMgr.h"
#include <iostream>
void TitleScene::Init(SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;
	ui.UiTitleInit();
}

void TitleScene::Update(Time dt, Time playTime, RenderWindow* window, View* mainView)
{
	ui.UiTitleUpdate(*window);

	if (InputMgr::GetKeyDown(Keyboard::Enter))
	{
		if (ui.GetMenuNum() == 1)
		{
			sceneManager->sceneSwitch(SceneType::GAME);
		}

		if (ui.GetMenuNum() == 3)
		{
			window->close();
		}
	}
}

void TitleScene::Draw(sf::RenderWindow* window, View* mainView, View* uiView)
{
	window->setView(*uiView);
	ui.UiTitleDraw(*window);
}

TitleScene::~TitleScene()
{
}