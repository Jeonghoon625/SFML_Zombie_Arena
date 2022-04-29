#include "Scene.h"
#include "../Utils/SceneManager.h"

void Scene::Init(SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;
}

void Scene::Update(Time dt, Time playTime, RenderWindow* window, View* mainView)
{
}

void Scene::Draw(RenderWindow* window, View* mainView, View* uiView)
{
}

Scene::~Scene()
{
}
