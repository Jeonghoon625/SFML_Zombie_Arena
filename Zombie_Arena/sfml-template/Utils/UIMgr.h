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
	// font
	Font fontZombieControl;
	// texture string
	std::string textureFileName;

	//title
	Sprite spriteTitle;
	Text textTitle;
	Text textMenu[3];
	int titleXpos;
	Vector2i menuPos;
	Texture textureCS;
	Sprite spriteCS;
	int menuNum;

	//game play
	Text textScore;
	Text textHighScore;
	Text textBullet;
	Text textWave;
	Text textZombies;

	RectangleShape healthBar;
	Vector2f healthBarsize;

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
	//title
	void UiTitleInit();
	void UiTitleUpdate(RenderWindow& window);
	void UiTitleDraw(RenderWindow& window);
	//game play
	void UiPlayInit(View& worldView);
	void UiPlayUpdate(Player& player);
	void UiPlayDraw(RenderWindow& window);
	//game level menu
	void UiMenuInit(View& uiView);
	void UiMenuUpdate(Player& player);
	void UiMenuDraw(RenderWindow& window);
};

