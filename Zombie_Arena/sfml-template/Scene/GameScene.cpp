#include "GameScene.h"
#include "../Utils/Utils.h"
#include "../Utils/InputMgr.h"
#include "../Utils/TextureHolder.h"
#include <sstream>

GameScene::GameScene() : ammoPickup(PickUp(PickUpTypes::Ammo)), healthPickup(PickUp(PickUpTypes::Health)), zombieNum(10), waveNum(1), isWaveClear(false), waveTimer(2.f), isGameClear(false)
{
}

void GameScene::Init(SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	Utils::SetOrigin(spriteCrosshair, Pivots::CC);

	arena.width = 1000;
	arena.height = 1000;

	CreateWalls();

	player.Spawn(arena, resolution, 0.f);

	CreateZombies(zombieNum);

	texBackground = TextureHolder::GetTexture("graphics/background_sheet.png");

	CreateBackGround();

	ammoPickup.SetArena(arena);
	healthPickup.SetArena(arena);

	items.push_back(&ammoPickup);
	items.push_back(&healthPickup);

	float healthBarwidth = player.GetHealth() * 3;
	float healthBarheight = 50;
	healthBarsize = Vector2f(healthBarwidth, healthBarheight);
	healthBar.setSize(healthBarsize);
	healthBar.setFillColor(Color::Red);
	Vector2f healthPos = Vector2f(resolution.x * 0.4f - healthBarwidth * 0.4f, resolution.y - 140.f);
	healthBar.setPosition(healthPos);
	Texture& texBackground = TextureHolder::GetTexture("graphics/background_sheet.png");

	fontZombiecontrol.loadFromFile("fonts/zombiecontrol.ttf");

	textAmmunition.setFont(fontZombiecontrol);
	textAmmunition.setString("ammunition = 120");
	textAmmunition.setFillColor(Color::White);
	textAmmunition.setCharacterSize(50);
	textAmmunition.setPosition(0, 0);

	textMagazine.setFont(fontZombiecontrol);
	textMagazine.setString("magazine = 12");
	textMagazine.setFillColor(Color::White);
	textMagazine.setCharacterSize(50);
	textMagazine.setPosition(0, 50);

	textReload.setFont(fontZombiecontrol);
	textReload.setString("Reload..");
	textReload.setFillColor(Color::Yellow);
	textReload.setCharacterSize(20);

	FloatRect reloadRect = textReload.getGlobalBounds();
	textReload.setOrigin(
		reloadRect.left + reloadRect.width * 0.5f,
		reloadRect.top + reloadRect.height * 0.5f
	);
	textReload.setPosition(resolution.x * 0.5f, resolution.y * 0.5f - 30.f);

	textWave.setFont(fontZombiecontrol);
	textWave.setString("Next Wave...");
	textWave.setFillColor(Color::White);
	textWave.setCharacterSize(100);
	FloatRect waveRect = textWave.getGlobalBounds();
	textWave.setOrigin(
		waveRect.left + waveRect.width * 0.5f,
		waveRect.top + waveRect.height * 0.5f
	);
	textWave.setPosition(resolution.x * 0.5f, resolution.y * 0.4f);

	textClear.setFont(fontZombiecontrol);
	textClear.setString("Game Clear.\nPress Enter");
	textClear.setFillColor(Color::White);
	textClear.setCharacterSize(100);
	FloatRect clearRect = textClear.getGlobalBounds();
	textClear.setOrigin(
		clearRect.left + clearRect.width * 0.5f,
		clearRect.top + clearRect.height * 0.5f
	);
	textClear.setPosition(resolution.x * 0.5f, resolution.y * 0.5f);
	ui.UiPlayInit();

	textOver.setFont(fontZombiecontrol);
	textOver.setString("Game Over.\nPress Enter");
	textOver.setFillColor(Color::White);
	textOver.setCharacterSize(100);
	FloatRect overRect = textOver.getGlobalBounds();
	textOver.setOrigin(
		overRect.left + overRect.width * 0.5f,
		overRect.top + overRect.height * 0.5f
	);
	textOver.setPosition(resolution.x * 0.5f, resolution.y * 0.5f);
	ui.UiPlayInit();
}

void GameScene::Update(Time dt, Time playTime, RenderWindow* window, View* mainView)
{
	if (!isGameClear && !isGameOver)
	{
		window->setMouseCursorVisible(false);

		spriteCrosshair.setPosition(InputMgr::GetMouseWorldPosition());

		player.Update(dt.asSeconds(), walls);
		mainView->setCenter(player.GetPosition());

		auto itZombie = zombies.begin();
		while (itZombie != zombies.end())
		{
			Zombie* zombie = *itZombie;
			zombie->Update(dt.asSeconds(), player.GetPosition());

			if (!zombie->IsALive())
			{
				Vector2f spawnPos = zombie->GetPosition();
				Blood* blood = new Blood();

				bloods.push_back(blood);
				blood->Spawn(spawnPos);

				delete zombie;
				zombieNum--;
				score++;
				itZombie = zombies.erase(itZombie);
			}
			else
			{
				++itZombie;
			}
		}

		auto itBlood = bloods.begin();
		while (itBlood != bloods.end())
		{
			Blood* blood = *itBlood;
			blood->Update(dt.asSeconds());

			if (!blood->IsActive())
			{
				delete blood;
				itBlood = bloods.erase(itBlood);
			}
			else
			{
				++itBlood;
			}
		}

		player.UpdateCollision(zombies);
		for (auto zombie : zombies)
		{
			if (zombie->UpdateCollision(playTime, player))
			{
				break;
			}
		}
		player.UpdateCollision(items);
		player.UpdateCollision(walls);

		ammoPickup.Update(dt.asSeconds());
		healthPickup.Update(dt.asSeconds());

		ui.UiPlayUpdate(*mainView, player, zombieNum, waveNum, score);

		if (zombieNum == 0)
		{
			if (waveNum < 3)
			{
				isWaveClear = true;
			}
			else
			{
				isGameClear = true;
			}
		}

		if (player.GetHealth() == 0)
		{
			isGameOver = true;
		}

		if (isWaveClear)
		{
			waveTimer -= dt.asSeconds();
			if (waveTimer <= 0)
			{
				isWaveClear = false;
				waveTimer = 2;
				NextStage();
			}
		}

		if (isGameClear)
		{
			NextStage();
		}
	}
	else
	{
		if(InputMgr::GetKeyDown(Keyboard::Enter))
		{
			sceneManager->sceneSwitch(SceneType::TITLE);
		}
	}
}

void GameScene::Draw(RenderWindow* window, View* mainView, View* uiView)
{
	window->clear();
	window->setView(*mainView);
	window->draw(tileMap, &texBackground);

	if (ammoPickup.IsSpawned())
	{
		window->draw(ammoPickup.GetSprite());
	}

	if (healthPickup.IsSpawned())
	{
		window->draw(healthPickup.GetSprite());
	}

	for (auto blood : bloods)
	{
		window->draw(blood->GetSprite());
	}

	for (auto zombie : zombies)
	{
		window->draw(zombie->GetSprite());
	}

	player.Draw(*window);
	window->draw(spriteCrosshair);
	window->setView(*uiView);
	ui.UiPlayDraw(*window);

	// 재장전 테스트용 //
	if (player.GetIsReload())
	{
		window->draw(textReload);
	}

	if (!isGameClear)
	{
		if (isWaveClear && waveNum <= 3)
		{
			window->draw(textWave);
		}
		
		if (isGameOver)
		{
			window->draw(textOver);
		}
	}
	else
	{
		window->draw(textClear);
	}

}

GameScene::~GameScene()
{
}

void GameScene::CreateWalls()
{
	for (auto v : walls)
	{
		delete v;
	}

	walls.clear();

	int offset = 50;
	Wall* wallUp = new Wall(0, arena.left, arena.width, offset);
	walls.push_back(wallUp);
	Wall* wallDown = new Wall(arena.top + arena.height - offset, arena.left, arena.width, offset);
	walls.push_back(wallDown);
	Wall* wallLeft = new Wall(offset, arena.left, offset, arena.height - 2 * offset);
	walls.push_back(wallLeft);
	Wall* wallRight = new Wall(offset, arena.left + arena.width - offset, offset, arena.height - 2 * offset);
	walls.push_back(wallRight);
}

int GameScene::CreateBackGround()
{
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;

	int cols = arena.width / TILE_SIZE;
	int rows = arena.height / TILE_SIZE;

	tileMap.setPrimitiveType(Quads);
	tileMap.resize(cols * rows * VERTS_IN_QUAD);

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
		{
			int index = r * cols + c;

			float x = c * TILE_SIZE;
			float y = r * TILE_SIZE;

			int vertexIndex = index * VERTS_IN_QUAD;

			tileMap[vertexIndex + 0].position = Vector2f(x, y);
			tileMap[vertexIndex + 1].position = Vector2f(x + TILE_SIZE, y);
			tileMap[vertexIndex + 2].position = Vector2f(x + TILE_SIZE, y + TILE_SIZE);
			tileMap[vertexIndex + 3].position = Vector2f(x, y + TILE_SIZE);

			int texIndex = Utils::RandomRange(0, TILE_TYPES);
			if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
			{
				texIndex = 3;
			}
			float offset = texIndex * TILE_SIZE;
			tileMap[vertexIndex + 0].texCoords = Vector2f(0.f, offset);
			tileMap[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE, offset);
			tileMap[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE, offset + TILE_SIZE);
			tileMap[vertexIndex + 3].texCoords = Vector2f(0.f, offset + TILE_SIZE);
		}
	}

	return cols * rows;
}

void GameScene::CreateZombies(int count)
{
	for (auto v : zombies)
	{
		delete v;
	}
	zombies.clear();

	int offset = 50;
	int minX = arena.left + offset;
	int maxX = arena.width - offset;
	int minY = arena.top + offset;
	int maxY = arena.height - offset;

	for (int i = 0; i < count; ++i)
	{
		int x = Utils::RandomRange(minX, maxX + 1);
		int y = Utils::RandomRange(minY, maxY + 1);
		ZombieTypes type = (ZombieTypes)Utils::RandomRange(0, (int)ZombieTypes::COUNT);
		Zombie* zombie = new Zombie();
		zombie->Spawn(type, arena, x, y, walls);
		zombies.push_back(zombie);
	}
}

void GameScene::NextStage()
{
	waveNum++;
	if (waveNum <= 3)
	{
		zombieNum = waveNum;
		CreateZombies(zombieNum);
	}
	else 
	{
		isGameClear = true;
	}
}


