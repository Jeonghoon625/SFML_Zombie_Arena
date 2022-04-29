#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../Utils/UIMgr.h"
#include "../Utils/SceneManager.h"

#define TITLE_XPOS 960
#define MENU_XPOS 880
#define MENU_YPOS 600

using namespace sf;
using namespace std;

class TitleScene : public Scene
{
private:
	SceneManager* sceneManager;
	UIMgr ui;
	Font fontKOMIKAP;
	Texture textureTitle;
	Sprite spriteTitle;
	Text textTitle;
	Text textMenu1;
	Text textMenu2;
	Text textMenu3;
	Texture textureCS;
	Sprite spriteCS;
	int menuPos;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(Time dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(sf::RenderWindow* window, View* mainView, View* uiView);
	virtual ~TitleScene();
};