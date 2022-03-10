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
	window.setFramerateLimit(60);
	sf::Clock clock;
	float dt = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
			{
				s->TemporaryChangepieceMethode();
			}
		}
		dt += clock.restart().asSeconds();
		if (dt >= 1)
		{
			window.clear();

			s->Update();

			s->Draw(window);

			window.display();

			dt = 0;
		}
	}
}
