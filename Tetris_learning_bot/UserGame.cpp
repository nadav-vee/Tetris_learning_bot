#include "UserGame.h"

using namespace std;

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
	// time variables
	float dt = 0;
	float dttwo = 0;
	int dtthree = 0;

	// game logic variables
	bool right = false;
	bool left = false;
	bool torotL = false;
	bool tomov = false;
	bool torotR = false;

	// general game variables
	bool restart = false;
	sf::Text highscore;
	sf::Text Score;

	highscore.setString("High Score = 0");
	highscore.setFillColor(sf::Color::Green);
	highscore.setPosition(sf::Vector2f(BH + BUFF, BH / 2));
	sf::Font font;
	font.loadFromFile(FONT);
	highscore.setFont(font);
	Score.setFont(font);

	while (window.isOpen())
	{
		cout << "" << endl;
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


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			torotL = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			torotR = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			s->TemporaryChangepieceMethode();
		}
		window.clear();
		if (dt >= 50)
		{


			if (dttwo >= 1000)
			{
				if (s->Update())
				{

				}

				dttwo = 0;
			}

			s->GameLogic(right, left, torotR, torotL);
			left = false;
			right = false;
			torotL = false;
			torotR = false;

			dt = 0;
		}
		s->Draw(window);

		window.draw(highscore);

		window.display();

		if (restart)
		{
			string newhighscore = "High Score = " + s->Score;
			highscore.setString(newhighscore);
			// delete s;
			s = new Stack();
			// time variables
			dt = 0;
			dttwo = 0;
			dtthree = 0;

			// game logic variables
			right = false;
			left = false;
			torotL = false;
			tomov = false;
			torotR = false;

			// general game variables
			restart = false;
		}
	}
}
