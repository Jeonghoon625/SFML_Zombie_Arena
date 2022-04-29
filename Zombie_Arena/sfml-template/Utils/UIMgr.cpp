#include "UIMgr.h"
#include <sstream>
#include "../Player/Player.h"
#include "../Utils/TextureHolder.h"
#include "../Utils/Utils.h"
#include "../Utils/InputMgr.h"

using namespace sf;
using namespace std;

UIMgr::UIMgr()
	:score(0), highScore(0), remainingBullet(24), allBullet(24), wave(0), zombies(20), hpBarWidth(10), health(50)
{
	fontZombieControl.loadFromFile("fonts/zombiecontrol.ttf");
}

void UIMgr::UiTitleInit()
{
	titleXpos = 960;
	menuPos = Vector2i(880, 660);

	textureFileName = ("graphics/background.png");
	spriteTitle.setTexture(TextureHolder::GetTexture(textureFileName));
	spriteTitle.setPosition(0, 0);

	textTitle.setFont(fontZombieControl);
	textTitle.setString("ZomBie Arena!");
	textTitle.setFillColor(Color::Red);
	textTitle.setCharacterSize(200);
	FloatRect TitleRect = textTitle.getLocalBounds();
	textTitle.setOrigin(
		TitleRect.left + TitleRect.width * 0.5f,
		TitleRect.top + TitleRect.height * 0.5f
	);
	textTitle.setPosition(titleXpos, 110);

	for (int i = 0; i < 3; i++)
	{
		textMenu[i].setFont(fontZombieControl);
		textMenu[i].setFillColor(Color::White);
		textMenu[i].setPosition(menuPos.x, menuPos.y + 50 * i);
		textMenu[i].setCharacterSize(50);
	}
	textMenu[0].setString("GAME START");
	textMenu[1].setString("HIGH SCORE");
	textMenu[2].setString("GAME EXIT");

	textureCS = TextureHolder::GetTexture("graphics/CS.png");
	spriteCS.setTexture(textureCS);
	spriteCS.setPosition(menuPos.x - 80, menuPos.y);
	menuNum = 1;
}


void UIMgr::UiTitleUpdate(RenderWindow& window)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Up) && menuNum != 1)
	{
		--menuNum;
		spriteCS.setPosition(menuPos.x - 80, spriteCS.getPosition().y - 50);
	}

	if (InputMgr::GetKeyDown(Keyboard::Key::Down) && selectButtonNum != 3)
	{
		++menuNum;
		spriteCS.setPosition(menuPos.x - 80, spriteCS.getPosition().y + 50);
	}

	if (InputMgr::GetKeyDown(Keyboard::Key::Enter))
	{
	}
}

void UIMgr::UiTitleDraw(RenderWindow& window)
{
	window.draw(spriteTitle);
	window.draw(textTitle);
	for (int i = 0; i < 3; i++)
	{
		window.draw(textMenu[i]);
	}
}

void UIMgr::UiPlayInit(View& worldView)
{
	// 폰트설정
	textScore.setFont(fontZombieControl);
	textHighScore.setFont(fontZombieControl);
	textBullet.setFont(fontZombieControl);
	textWave.setFont(fontZombieControl);
	textZombies.setFont(fontZombieControl);
	//string
	textScore.setString("SCORE:0");
	textHighScore.setString("HI SCORE:0");
	textBullet.setString("24/24");
	textWave.setString("WAVE:0");
	textZombies.setString("ZOMBIES:500");
	//CharacterSize
	textScore.setCharacterSize(50);
	textHighScore.setCharacterSize(50);
	textBullet.setCharacterSize(50);
	textWave.setCharacterSize(50);
	textZombies.setCharacterSize(50);
	// color
	textScore.setFillColor(Color::White);
	textHighScore.setFillColor(Color::White);
	textBullet.setFillColor(Color::White);
	textWave.setFillColor(Color::White);
	textZombies.setFillColor(Color::White);

	stringstream ss;	//string score
	ss << "SCORE:" << score;
	textScore.setString(ss.str());
	stringstream sh;	//string high score
	sh << "HI SCORE:" << highScore;
	textHighScore.setString(sh.str());
	stringstream sb;
	sb << remainingBullet << "/" << allBullet;
	textBullet.setString(sb.str());
	stringstream sw;
	sw << "WAVE:" << wave;
	textWave.setString(sw.str());
	stringstream sz;
	sz << "ZOMBIES:" << zombies;
	textZombies.setString(sz.str());

	// position
	textScore.setPosition(worldView.getSize().x * 0.05f, worldView.getSize().y * 0.05f);
	textHighScore.setPosition(worldView.getSize().x * 0.8f, worldView.getSize().y * 0.05f);
	textBullet.setPosition(worldView.getSize().x * 0.1f, worldView.getSize().y * 0.9f);
	textWave.setPosition(worldView.getSize().x * 0.65f, worldView.getSize().y * 0.9f);
	textZombies.setPosition(worldView.getSize().x * 0.85f, worldView.getSize().y * 0.9f);

	Utils::SetOrigin(healthBar, Pivots::CC);
	float healthBarwidth = 300;
	float healthBarheight = 50;
	healthBarsize = Vector2f(healthBarwidth, healthBarheight);
	healthBar.setSize(healthBarsize);
	Vector2f healthPos = Vector2f(worldView.getSize().x * 0.4f - healthBarwidth * 0.4f, worldView.getSize().y - 140.f);
	healthBar.setPosition(healthPos);
	healthBar.setFillColor(Color::Red);
}

void UIMgr::UiPlayUpdate(Player& player)
{
	stringstream ss;	//string score
	ss << "SCORE:" << score;
	textScore.setString(ss.str());
	stringstream sh;	//string high score
	sh << "HI SCORE:" << highScore;
	textHighScore.setString(sh.str());
	stringstream sb;
	sb << remainingBullet << "/" << allBullet;
	textBullet.setString(sb.str());
	stringstream sw;
	sw << "WAVE:" << wave;
	textWave.setString(sw.str());
	stringstream sz;
	sz << "ZOMBIES:" << zombies;
	textZombies.setString(sz.str());

	healthBarsize.x = player.GetHealth() * 3;	//체력 바
	healthBar.setSize(healthBarsize);
}

void UIMgr::UiPlayDraw(RenderWindow& window)
{
	window.draw(textScore);
	window.draw(textHighScore);
	window.draw(textBullet);
	window.draw(textWave);
	window.draw(textZombies);
	window.draw(healthBar);
}

void UIMgr::UiMenuInit(View& uiView)
{
	selectButtonNum = 1;
	characterSize = 75;

	textureFileName = ("graphics/background.png");
	background.setTexture(TextureHolder::GetTexture(textureFileName));
	background.setPosition(0, 0);

	textureFileName = ("graphics/select_button.png");
	selectButton.setTexture(TextureHolder::GetTexture(textureFileName));
	selectButton.setPosition(uiView.getSize().x * 0.25f - 50, uiView.getSize().y * 0.5f - characterSize * 3 + 25);

	for (int i = 0; i < 6; i++)
	{
		textSelect[i].setFont(fontZombieControl);
		textSelect[i].setCharacterSize(characterSize);
		textSelect[i].setFillColor(Color::White);
		FloatRect textRect = textSelect[i].getLocalBounds();

		textSelect[i].setPosition(uiView.getSize().x * 0.25f, uiView.getSize().y * 0.5f - characterSize * 3 + 75 * i);
	}

	//string
	textSelect[0].setString("1-INCREASED RATE OF FIRE");
	textSelect[1].setString("2-INCREASED CLIP SIZE(NEXT RELOAD)");
	textSelect[2].setString("3-INCREASED MAX HEALTH");
	textSelect[3].setString("4-INCREASED RUN SPEED");
	textSelect[4].setString("5-MORE AND BETTER HEALTH PICKUPS");
	textSelect[5].setString("6-More And Better Ammo PICKUPS");
}

void UIMgr::UiMenuUpdate(Player& player)
{
	if (InputMgr::GetKeyDown(Keyboard::Key::Up) && selectButtonNum != 1)
	{
		--selectButtonNum;
		selectButton.setPosition(selectButton.getPosition().x, selectButton.getPosition().y - characterSize);
	}

	if (InputMgr::GetKeyDown(Keyboard::Key::Down) && selectButtonNum != 6)
	{
		++selectButtonNum;
		selectButton.setPosition(selectButton.getPosition().x, selectButton.getPosition().y + characterSize);
	}

	if (InputMgr::GetKeyDown(Keyboard::Key::Enter))
	{
	}

}

void UIMgr::UiMenuDraw(RenderWindow& window)
{
	window.draw(background);
	for (int i = 0; i < 6; i++)
	{
		window.draw(textSelect[i]);
	}
	window.draw(selectButton);
}
