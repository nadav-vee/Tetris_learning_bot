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
	// AssetManager manager;
	Stack* s = new Stack();
	sf::RenderWindow window(sf::VideoMode(W, H), "TETRIS!");
	sf::Clock clock;
	// time variables

	float dtCounter = 0;
	float dtUpdate = 0;
	float dtMov = 0;
	float dtRot = 0;

	// game logic variables
	bool torotR = false;
	bool torotL = false;
	bool right = false;
	bool left = false;
	bool tomov = false;
	bool TmpChgPceMthd = false;
	bool dropp = false;
	bool fasterdown = false;
	bool hold = false;

	// bug fixes with events
	bool canPressSpace = true;
	bool canPressRShift = true;
	bool canPressReturn = true;
	bool canPressUp = true;

	// general game variables
	bool notpaused = true;
	bool* restart = (bool*)malloc(sizeof(bool));
	*restart = false;

	// Text and scoring:
	sf::Text highscoreTX;
	sf::Text Score;
	sf::Text LosingMessage;
	sf::Font* font = new sf::Font();
	HighScore = 0;
	font->loadFromFile(FONT); // font init
	highscoreTX.setFont(*font);
	highscoreTX.setString("High Score = 0");
	highscoreTX.setFillColor(sf::Color::Green);
	highscoreTX.setPosition(sf::Vector2f(SCOREALLIGN, H / 2));
	highscoreTX.setCharacterSize(20);
	//
	Score.setFont(*font);
	Score.setString("Score = 0");
	Score.setFillColor(sf::Color::Green);
	Score.setPosition(sf::Vector2f(SCOREALLIGN, H / 2 + 20));
	Score.setCharacterSize(25);
	//
	LosingMessage.setFont(*font);
	LosingMessage.setString("YOU LOST!");
	LosingMessage.setFillColor(sf::Color::Green);
	LosingMessage.setCharacterSize(30);
	sf::Vector2f LosingMessageBounds = { LosingMessage.getGlobalBounds().width, LosingMessage.getGlobalBounds().height };
	LosingMessage.setOrigin(LosingMessageBounds.x / 2, LosingMessageBounds.y / 2);
	LosingMessage.setPosition(W / 4, H / 4);

	// Design variables:
	sf::RectangleShape* upperHoldLine = new sf::RectangleShape(
		sf::Vector2f(PLW * 2, 5));
	upperHoldLine->setPosition(sf::Vector2f(W - PLW * 2, H - (PLW * 1.5 + BUFF)));
	upperHoldLine->setFillColor(sf::Color::Green);


	while (window.isOpen())
	{
		dtCounter = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed &&
					event.key.code == sf::Keyboard::Escape))
				window.close();
			if (event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::Space)
			{
				canPressSpace = true;
			}
			if (event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::D)
			{
				*restart = true;
			}
			if (event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::Up)
			{
				canPressUp = true;
			}
			if (event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::RShift)
			{
				canPressReturn = false;
			}
			if (event.type == sf::Event::KeyPressed
				&& event.key.code == sf::Keyboard::Return)
			{
				canPressRShift = false;
			}
			if (event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::RShift)
			{
				canPressReturn = true;
			}
			if (event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::Return)
			{
				canPressRShift = true;
			}
			if (event.type == sf::Event::KeyReleased
				&& event.key.code == sf::Keyboard::P)
			{
				notpaused = (notpaused) ? false : true;
			}

		}
		window.clear();

		if (notpaused)
		{
			dtUpdate += dtCounter;
			dtMov += dtCounter;
			dtRot += dtCounter;

			if (dtMov >= 0.150f)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					right = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					left = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					fasterdown = true;
					dtUpdate = 0;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					TmpChgPceMthd = true;
				}
				dtMov = 0;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canPressSpace)
			{
				dropp = true;
				canPressSpace = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canPressUp)
			{
				hold = true;
				canPressUp = false;
			}

			if (dtRot >= 0.160f)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && canPressReturn)
				{
					torotL = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && canPressRShift)
				{
					torotR = true;
				}
				dtRot = 0;
			}

			s->GameLogic(right, left, torotR, torotL, TmpChgPceMthd, dropp, fasterdown, hold);
			left = false;
			right = false;
			TmpChgPceMthd = false;
			torotL = false;
			torotR = false;
			dropp = false;
			fasterdown = false;
			hold = false;

			if (dtUpdate >= 0.900f)
			{

				s->Update(restart);
				string sco = "Score = ";
				sco += std::to_string(s->Score);
				Score.setString(sco);
				if (s->Score > HighScore)
				{
					HighScore = s->Score;
				}
				sco = "High Score = ";
				sco += to_string(HighScore);
				highscoreTX.setString(sco);
				dtUpdate = 0;
			}
		}
		s->Draw(window);

		window.draw(Score);
		window.draw(highscoreTX);
		window.draw(*upperHoldLine);

		window.display();
		////////////////////////////////////////
		if (*restart)
		{
			string sco = "High Score = ";
			sco += std::to_string(HighScore);
			highscoreTX.setString(sco);
			// delete s;
			s = new Stack();
			// time variables
			float dtCounter = 0;
			float dtUpdate = 0;
			float dtMov = 0;
			float dtRot = 0;

			// game logic variables
			left = false;
			right = false;
			TmpChgPceMthd = false;
			torotL = false;
			torotR = false;
			dropp = false;
			fasterdown = false;
			hold = false;


			// general game variables
			*restart = false;

			sf::RenderWindow windowyoulost(sf::VideoMode(W / 2, H / 2), "welp you dieded");
			while (windowyoulost.isOpen())
			{
				dtCounter = clock.restart().asSeconds();

				sf::Event eventt;
				while (windowyoulost.pollEvent(eventt))
				{
					if (eventt.type == sf::Event::Closed)
						windowyoulost.close();
					if (eventt.type == sf::Event::KeyPressed
						&& eventt.key.code == sf::Keyboard::Space)
					{
						windowyoulost.close();
						canPressSpace = false;
					}
				}

				windowyoulost.clear();

				windowyoulost.draw(LosingMessage);

				windowyoulost.display();
			}
		}
		////////////////////////////////////////
	}
	free(restart);
}
