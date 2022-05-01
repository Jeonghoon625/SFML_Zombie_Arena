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
	View* mainView; //���� ������Ʈ (sprite)
	View* uiView; //�ؽ�Ʈ UI (�޴�, ������)
	Vector2i resolution; //�ػ�

	SceneManager sceneManager; //���Ŵ���
	TextureHolder textureHolder; //���ҽ��Ŵ���(�ؽ���, ����, ��Ʈ)
	//�ִϸ��̼� �Ŵ���
	//�׿ܿ� �پ��� �Ŵ���... �浹 �Ŵ���, �̵� �Ŵ���

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