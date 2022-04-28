#include "Framework.h"

void Framework::Init(int screenWidth, int screenHeight, std::string gameTitle)
{
	sf::VideoMode vm(screenWidth, screenHeight); //inital size hd
	window = new sf::RenderWindow(vm, gameTitle, sf::Style::Default);
	
	//ResourceManager::GetInstance().Init();
	sceneManager.Init();
}

void Framework::Update(float deltaTime)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window->close();
				break;
			}

		default:
			break;
		}
	}

	sceneManager.Update(deltaTime);
}

void Framework::Draw(sf::RenderWindow* window)
{
	window->clear();

	sceneManager.Draw(window);

	window->display();
}

int Framework::Run() //Game Loop
{
	while (window->isOpen())
	{
		sf::Time dt = clock.restart();
		Update(dt.asSeconds());
		Draw(window);
	}

	return 0;
}

