#include "Framework.h"

bool Framework::Initialize()
{
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	window = new RenderWindow(VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Fullscreen);
	mainView = new View(FloatRect(0, 0, resolution.x, resolution.y));
	uiView = new View(FloatRect(0, 0, resolution.x, resolution.y));
	
	InputMgr::Init();

	sceneManager.Init();
	//ResourceManager::GetInstance().Init();

	return true;
}

void Framework::Update()
{
	InputMgr::ClearInput();

	Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			window->close();
			break;
		
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape)
			{
				window->close();
				break;
			}

		default:
			break;
		}

		InputMgr::ProcessInput(event);
	}

	InputMgr::Update(dt.asSeconds(), *window, *mainView);
	sceneManager.Update(dt, playTime, window, mainView);
}

void Framework::Draw()
{
	window->clear();
	sceneManager.Draw(window, mainView, uiView);
	window->display();
}

int Framework::Run() //Game Loop
{
	while (window->isOpen())
	{
		dt = clock.restart(); //Frame
		playTime += dt;
		Update();
		Draw();
	}

	return 0;
}

Framework::~Framework()
{
	delete window;
	delete mainView;
	delete uiView;
}