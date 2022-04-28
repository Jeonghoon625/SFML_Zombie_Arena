#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Player;

enum class levelMenu : int
{
	levelMenu1 = 1,
	levelMenu2,
	levelMenu3,
	levelMenu4,
	levelMenu5,
	levelMenu6,
};

class UIMgr
{
private:
	//game play
	std::string textureFileName;

	Text textScore;
	Text textHighScore;
	Text textBullet;
	Text textWave;
	Text textZombies;

	RectangleShape healthBar;
	Vector2f healthBarsize;

	Font fontZombieControl;

	int score;
	int highScore;
	int remainingBullet;
	int allBullet;
	int wave;
	int zombies;

	int health;
	int hpBarWidth;
	// game level menu
	Text textSelect[6];

	Sprite background;
	Sprite selectButton;

	int characterSize;
	int selectButtonNum;
	

public:
	UIMgr();
	//game play
	void UiPlayInit(View& worldView);
	void UiPlayUpdate(Player& player);
	void UiPlayDraw(RenderWindow& window);
	//game level menu
	void UiMenuInit(View& uiView);
	void UiMenuUpdate(Player& player);
	void UiMenuDraw(RenderWindow& window);
};

