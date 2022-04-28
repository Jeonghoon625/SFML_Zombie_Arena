#pragma once
#include "SFML/Graphics.hpp"
#include "../Scene/Headers/Scene.h"
#include "../Scene/Headers/TitleScene.h"
#include "../Scene/Headers/Scene.h"

class SceneManager
{
private:
	Scene* currentScene;

public:
	void Init();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow* window);
};