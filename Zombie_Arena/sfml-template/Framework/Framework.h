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
	View* mainView; //게임 오브젝트 (sprite)
	View* uiView; //텍스트 UI (메뉴, 아이템)
	Vector2i resolution; //해상도

	SceneManager sceneManager; //씬매니저
	TextureHolder textureHolder; //리소스매니저(텍스쳐, 사운드, 폰트)
	//애니메이션 매니저
	//그외에 다양한 매니저... 충돌 매니저, 이동 매니저

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