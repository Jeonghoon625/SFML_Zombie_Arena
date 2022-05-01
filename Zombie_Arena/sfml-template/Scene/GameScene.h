#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../Player/Player.h"
#include "../Wall/Wall.h"
#include "../Zombie/Zombie.h"
#include "../PickUp/PickUp.h"
#include "../Blood/Blood.h"
#include "../Utils/SceneManager.h"
#include "../Utils/UIMgr.h"

using namespace sf;
using namespace std;

class GameScene : public Scene
{
private:
	SceneManager* sceneManager;
	UIMgr ui;
	Sprite spriteCrosshair;
	Texture textureCrosshair;
	Texture texBackground;

	IntRect arena;

	vector <Zombie*> zombies;
	vector<Blood*> bloods;
	int zombieNum;

	Player player;
	
	vector <Wall*> walls;
	VertexArray tileMap;
	Vector2i resolution;

	vector<PickUp*> items;
	PickUp ammoPickup;
	PickUp healthPickup;

	Font fontZombiecontrol;
	Text textAmmunition;
	Text textMagazine;
	Text textReload;
	Text textWave;
	Text textClear;
	Text textOver;
	RectangleShape healthBar;
	Vector2f healthBarsize;
	bool isWaveClear;
	float waveTimer;
	int waveNum;
	
	bool isGameClear;

	int score;
	bool isGameOver;

public:
	GameScene();
	virtual void Init(SceneManager* sceneManager);
	virtual void Update(Time dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView, View* uiView);
	virtual ~GameScene();

	void CreateWalls();
	int CreateBackGround();
	void CreateZombies(int count);
	void NextStage();
};