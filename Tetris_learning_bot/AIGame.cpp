#include "AIGame.h"
#define RAND_HEURISTIC_RANGE() (rand()/float(RAND_MAX)* 2 + 1.0)

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
	}
}

void AIGame::Update(float dt)
{

	ai->SetUpdateFrequency(1);
	// controller
	if (ai)
	{
		ai->timeUntilUpdate -= dt;

		while (ai->timeUntilUpdate <= 0.0f)
		{
			ai->timeUntilUpdate += ai->updateFrequency;
			if (!ai->currentMove.used)
			{
				if (ai->currentMove.swapPiece)
				{
					ai->currentMove.used = true;
					ai->tetris->AIHold();
				}

				else
				{
					bool shouldDrop = true;
					if (ai->tetris->curpiece->maxRotations < ai->currentMove.numRotations)
					{
						shouldDrop = false;
						ai->tetris->RotateR();
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
			}
		}
	} // move

	// eval
	if (ai)
	{
		if (!ai->initialized)
		{
			float flHeuristicWidth = ai->aiHeuristicRange.y - ai->aiHeuristicRange.x;
			ai->initialized = true;
			ai->heuristics.push_back(new AIHeuristic_AggregateHeight(1/*-2.00 * RAND_HEURISTIC_RANGE()*/));
			////comp->m_heuristics.push_back(new AIHeuristic_CompletedLines(2));
			////comp->m_heuristics.push_back(new AIHeuristic_HighestCol(-2.75));
			////comp->m_heuristics.push_back(new AIHeuristic_DeepestHole(2.0 * RAND_HEURISTIC_RANGE()));
			//comp->m_heuristics.push_back(new AIHeuristic_GameLoss(-1 * RAND_HEURISTIC_RANGE()));
			ai->heuristics.push_back(new AIHeuristic_Holes(1/*-5.5f*/));
			ai->heuristics.push_back(new AIHeuristic_Blockade(1/*-.4f * RAND_HEURISTIC_RANGE()*/));
			ai->heuristics.push_back(new AIHeuristic_Bumpiness(1/*-1.55f * RAND_HEURISTIC_RANGE()*/));
			// ai->debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Agg Height" });
			//comp->m_debugHeuristics.push_back(AIDebug{ 0.0f, "Completed Lines" });
			//comp->m_debugHeuristics.push_back(AIDebug{ 0.0f, "Highest Column" });
			//comp->m_debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Deepest Hole" });
			/*ai->debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Game Loss" });
			ai->debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Holes" });
			ai->debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Blockade" });
			ai->debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Bumpiness" });*/
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

