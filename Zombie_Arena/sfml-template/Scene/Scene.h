#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Scene
{
public:
	virtual void Init();
	virtual void Update(Time dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window , View* mainView , View* uiView);
	virtual ~Scene();
};