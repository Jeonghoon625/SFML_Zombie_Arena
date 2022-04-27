#include <iostream>
#include "SFML/Graphics.hpp"
#include "Utils/TextureHolder.h"
#include "Utils/InputMgr.h"
#include "Utils/Utils.h"
#include "Player/Player.h"
#include "Zombie/Zombie.h"
#include "Wall/Wall.h"
#include "Bullet/Bullet.h"

using namespace sf;
using namespace std;

int CreateBackGround(VertexArray& va, IntRect arena)
{
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;

	int cols = arena.width / TILE_SIZE;
	int rows = arena.height / TILE_SIZE;

	va.setPrimitiveType(Quads);
	va.resize(cols * rows * VERTS_IN_QUAD);


	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
		{
			int index = r * cols + c;

			float x = c * TILE_SIZE;
			float y = r * TILE_SIZE;

			int vertexIndex = index * VERTS_IN_QUAD;

			va[vertexIndex + 0].position = Vector2f(x, y);
			va[vertexIndex + 1].position = Vector2f(x + TILE_SIZE, y);
			va[vertexIndex + 2].position = Vector2f(x + TILE_SIZE, y + TILE_SIZE);
			va[vertexIndex + 3].position = Vector2f(x, y + TILE_SIZE);

			int texIndex = Utils::RandomRange(0, TILE_TYPES);
			if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
			{
				texIndex = 3;
			}
			float offset = texIndex * TILE_SIZE;
			va[vertexIndex + 0].texCoords = Vector2f(0.f, offset);
			va[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE, offset);
			va[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE, offset + TILE_SIZE);
			va[vertexIndex + 3].texCoords = Vector2f(0.f, offset + TILE_SIZE);
		}
	}

	return cols * rows;
}

void CreateZombies(std::vector<Zombie*>& zombies, int count, IntRect arena, std::vector <Wall*> walls)
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

void CreateWalls(std::vector<Wall*>& walls, IntRect arena)
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

int main()
{
	TextureHolder textureHolder;
	Vector2i resolution;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Default);

	View mainView(FloatRect(0, 0, resolution.x, resolution.y));

	InputMgr::Init();

	IntRect arena;
	arena.width = 1000;
	arena.height = 1000;

	std::vector <Wall* > walls;
	CreateWalls(walls, arena);

	Player player;
	player.Spawn(arena, resolution, 0.f);

	std::vector<Zombie*> zombies;
	CreateZombies(zombies, 200, arena, walls);

	Clock clock;
	
	Texture& texBackground = TextureHolder::GetTexture("graphics/background_sheet.png");

	texBackground.loadFromFile("graphics/background_sheet.png");

	VertexArray tileMap;
	CreateBackGround(tileMap, arena);

	int i = 0;
	while (window.isOpen())
	{
		Time dt = clock.restart();
		InputMgr::ClearInput();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			InputMgr::ProcessInput(event);
		}

		InputMgr::Update(dt.asSeconds());

		player.Update(dt.asSeconds(), walls);

		mainView.setCenter(player.GetPosition());

		for (auto zombie : zombies)
		{
			zombie->Update(dt.asSeconds(), player.GetPosition());
		}
		
		window.clear();
		window.setView(mainView);
		window.draw(tileMap, &texBackground);
		window.draw(player.GetSprite());
		
		for (auto zombie : zombies)
		{
			window.draw(zombie->GetSprite());
		}
		
		window.display();
	}

	return 0;
}