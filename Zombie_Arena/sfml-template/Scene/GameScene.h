#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../Player/Player.h"
#include "../Wall/Wall.h"
#include "../Zombie/Zombie.h"
#include "../PickUp/PickUp.h"
#include "../Blood/Blood.h"

using namespace sf;
using namespace std;

class GameScene : public Scene
{
private:
	Sprite spriteCrosshair;
	Texture textureCrosshair;
	Texture texBackground;

	IntRect arena;

	vector <Zombie*> zombies;
	vector<Blood*> bloods;

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
	RectangleShape healthBar;
	Vector2f healthBarsize;
	
public:
	GameScene();
	virtual void Init();
	virtual void Update(Time dt, Time playTime, RenderWindow* window, View* mainView);
	virtual void Draw(RenderWindow* window, View* mainView, View* uiView);
	virtual ~GameScene();

	void CreateWalls();
	int CreateBackGround();
	void CreateZombies(int count);
};