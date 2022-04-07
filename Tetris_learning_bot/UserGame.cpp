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

	float dtCounter = 0;
	float dtGameLogic = 0;
	float dtUpdate = 0;
	float dtMov = 0;
	float dtRot = 0;

	// game logic variables
	bool torotR = true;
	bool torotL = true;
	bool right = false;
	bool left = false;
	bool tomov = false;
	bool TmpChgPceMthd = false;

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
		dtCounter = clock.restart().asSeconds();
		dtGameLogic += dtCounter;
		dtUpdate += dtCounter;
		dtMov += dtCounter;
		dtRot += dtCounter;
		//cout << "" << endl;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (dtMov >= 0.1)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				right = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				left = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				TmpChgPceMthd = true;
			}
			dtMov = 0;
		}
		if (dtRot >= 0.4)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				torotL = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				torotR = true;
			}
		}

		if (dtGameLogic >= 0.5)
		{


			s->GameLogic(right, left, torotR, torotL, TmpChgPceMthd);
			left = false;
			right = false;
			TmpChgPceMthd = false;
			torotL = false;
			torotR = false;

			dtGameLogic = 0;
		}
		if (dtUpdate >= 1)
		{
			if (s->Update())
			{

			}
			dtUpdate = 0;
		}
		window.clear();

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
			/*dt = 0;
			dttwo = 0;
			dtthree = 0;*/

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
