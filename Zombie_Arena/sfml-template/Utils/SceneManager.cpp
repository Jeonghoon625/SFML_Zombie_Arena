#include "SceneManager.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"

void SceneManager::Init()
{
	//sceneSwitch(SceneType::TITLE);
	sceneSwitch(SceneType::GAME);
}

void SceneManager::Update(Time dt, Time playTime, RenderWindow* window, View* mainView)
{
	currentScene->Update(dt, playTime, window, mainView);
}

void SceneManager::Draw(sf::RenderWindow* window, View* mainView, View* uiView)
{
	currentScene->Draw(window, mainView, uiView);
}

void SceneManager::sceneSwitch(SceneType sceneType)
{
	sceneRelease();

	switch (sceneType)
	{
	case SceneType::TITLE:
		currentScene = new TitleScene();
		break;

	case SceneType::MENU:
		//currentScene = new TitleScene();
		break;

	case SceneType::GAME:
		currentScene = new GameScene();
		break;

	}

	sceneInit();
}

void SceneManager::sceneRelease()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
	}
	
}

void SceneManager::sceneInit()
{
	currentScene->Init();
}
