#pragma once
#include "SFML/Graphics.hpp"
#include "../Scene/Scene.h"

using namespace sf;

enum class SceneType
{
	TITLE, MENU, GAME
};

class SceneManager
{
private:
	Scene* currentScene;

public:
	void Init();
	void Update(Time dt, Time playTime, RenderWindow* window, View* mainView);
	void Draw(RenderWindow* window, View* mainView, View* uiView);
	void sceneSwitch(SceneType sceneType);
	void sceneRelease();
	void sceneInit();
};