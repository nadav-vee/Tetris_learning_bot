#include "UserGame.h"

UserGame::UserGame()
{

	// init logic
}

void UserGame::Start()
{
	// game logic
	// change constants
	AssetManager manager;
	Stack* s = new Stack();
	sf::RenderWindow window(sf::VideoMode(W, H), "TETRIS DEEZ NUTS!");
	sf::Clock clock;
	float dt = 0, dttwo = 0;
	int dtthree = 0;
	bool right = false, left = false;
	bool torot = false, tomov = false;
	while (window.isOpen())
	{
		//std::cout << dt << std::endl;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		dt += clock.restart().asMilliseconds();
		dttwo += dt;
		dtthree += dt;
		if (dtthree >= 10)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				right = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				left = true;
			}
			dtthree = 0;
		}
		std::cout << s->curpiece->StackIndPos.x << std::endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			torot = true;
		}
		if (dt >= 150)
		{
			window.clear();
			if (torot)
			{
				s->curpiece->Rotate();
				torot = false;
			}
			if (right)
			{
				s->curpiece->Move(1);
				right = false;
			}
			if (left)
			{
				s->curpiece->Move(-1);
				left = false;
			}

			if (dttwo >= 1000)
			{
				s->Update();

				dttwo = 0;
			}

			s->Draw(window);


			dt = 0;
			window.display();
		}
	}
}
