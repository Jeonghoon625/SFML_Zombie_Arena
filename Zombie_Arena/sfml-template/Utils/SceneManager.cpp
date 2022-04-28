#include "SceneManager.h"
#include "../Scene/Headers/TitleScene.h"

void SceneManager::Init()
{
	currentScene = new TitleScene();
	currentScene->Init();
}

void SceneManager::Update(float deltaTime)
{
	currentScene->Update(deltaTime);
}

void SceneManager::Draw(sf::RenderWindow* window)
{
	currentScene->Draw(window);
}