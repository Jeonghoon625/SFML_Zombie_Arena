#pragma once
#include <SFML/Graphics.hpp>

class SceneManager;

using namespace sf;

class Scene
{
protected:
	SceneManager* sceneManager;

public:
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(Time dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window , View* mainView , View* uiView);
	virtual ~Scene();
};