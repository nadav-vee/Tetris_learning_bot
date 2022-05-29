#include "AIGame.h"
using namespace std;

AIGame::AIGame()
{
}

void AIGame::Start(sf::RenderWindow& window)
{
	// srand(unsigned int(time(NULL)));
	// systems
	//sf::View playerView;
	ai = new AI();

	bool* restart = new bool();
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





	bool paused = false;
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P)
				{
					paused = !paused;
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape)
			{
				return;
			}
		}

		window.clear();

		sf::Time time = clock.restart();
		if (!paused)
		{
			Update(time.asSeconds());
			string sco = "Score = ";
			sco += std::to_string(ai->tetris->Score);
			Score.setString(sco);
			if (ai->tetris->Score > HighScore)
			{
				HighScore = ai->tetris->Score;
			}
			sco = "High Score = ";
			sco += to_string(HighScore);
			highscoreTX.setString(sco);
		}

		Draw(window, time.asSeconds());
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
			delete ai->tetris;
			ai->tetris = new Stack();


			// general game variables
			*restart = false;

			sf::RenderWindow windowyoulost(sf::VideoMode(W / 2, H / 2), "welp you dieded");
			while (windowyoulost.isOpen())
			{
				sf::Event eventt;
				while (windowyoulost.pollEvent(eventt))
				{
					if (eventt.type == sf::Event::Closed)
						windowyoulost.close();
					if (eventt.type == sf::Event::KeyPressed
						&& eventt.key.code == sf::Keyboard::Space)
					{
					}
				}

				windowyoulost.clear();

				windowyoulost.draw(LosingMessage);

				windowyoulost.display();
			}
		}
		////////////////////////////////////////
	}
}

void AIGame::Update(float dt)
{

	ai->SetUpdateFrequency(0.5);
	// controller
	if (ai)
	{
		ai->timeUntilUpdate -= dt;

		while (ai->timeUntilUpdate <= 0.0f)
		{
			ai->timeUntilUpdate += ai->updateFrequency;
			if (!ai->currentMove.used)
			{
				if (ai->currentMove.swapPiece && !ai->tetris->didInsertToHold)
				{
					ai->currentMove.used = true;
					ai->tetris->Hold();
				}

				else
				{
					bool shouldDrop = true;
					if (0 < ai->currentMove.numRotations)
					{
						shouldDrop = false;
						ai->tetris->ResetcurpiecePositionForRotation();
						ai->tetris->RotateR();
						ai->tetris->ResetcurpiecePosition();
						ai->currentMove.numRotations--;
					}
					else if (ai->tetris->curpiece->Xpos < ai->currentMove.col)
					{
						shouldDrop = false;
						ai->tetris->Move(1);
					}
					else if (ai->tetris->curpiece->Xpos > ai->currentMove.col)
					{
						shouldDrop = false;
						ai->tetris->Move(-1);
					}

					if (shouldDrop)
					{
						ai->currentMove.used = true;
						bool* Res = new bool();
						ai->tetris->NewPieceAndDrop(Res);
						if (*Res)
							ai->tetris->resetCount++;
					}
				}

				ai->tetris->CopyPieceFunc(buff::PIECETOBUFF);
				ai->tetris->SetShadow();
			}
		}
	} // move

	// eval
	if (ai)
	{
		if (!ai->initialized)
		{
			ai->initialized = true;
			ai->heuristics.push_back(new AIHeuristic_AggregateHeight(-2.00));
			ai->heuristics.push_back(new AIHeuristic_Holes(-5.5f));
			ai->heuristics.push_back(new AIHeuristic_Blockade(-0.4f));
			ai->heuristics.push_back(new AIHeuristic_Bumpiness(-1.55f));
		}

		ai->timeSinceLastUpdate += dt;

		// move
		Stack* current = ai->tetris;
		if (ai->CanFindMove() && ai->NeedsNewMove())
		{
			ai->FindBestMove();
			DesiredMoveSet moveset = ai->GetBestMove();
			ai->SetCurrentMove(moveset);
		}
	}
}

void AIGame::Draw(sf::RenderWindow& window, float dt)
{
	// move

	//// Debug
	Stack* current = ai->tetris;
	current->Draw(window);

	// 
}

