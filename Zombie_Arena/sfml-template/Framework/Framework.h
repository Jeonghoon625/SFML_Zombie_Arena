#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/SceneManager.h"
#include "../Utils/InputMgr.h"
#include "../Utils/UIMgr.h"
#include "../Utils/TextureHolder.h"

using namespace sf;

class Framework
{
private:
	RenderWindow* window;
	View* mainView;
	View* uiView;
	Vector2i resolution;

	SceneManager sceneManager;
	TextureHolder textureHolder;
	UIMgr uiMgr;

	Clock clock;
	Time playTime;
	Time dt;

public:
	bool Initialize();
	void Update();
	void Draw();
	int Run();

	~Framework();
};