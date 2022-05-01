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
	void sceneSwitch(SceneType sceneType); //currentScene을 교체해주는 함수
	void sceneRelease(); //scene이 동적으로 생성됐으면은 지워야 delete 
	void sceneInit(); //current scene이 교체되면 새로 생성하는 씬을 초기화해줘야함...
	
};