#include "AIGame.h"
#define RAND_HEURISTIC_RANGE() (rand()/float(RAND_MAX)* flHeuristicWidth + m_aiHeuristicRange.x)


AIGame::AIGame()
{
}

void AIGame::Start()
{
	srand(unsigned int(time(NULL)));
	// systems
	sf::ContextSettings windowSettings;
	windowSettings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(W, H), "TETRIS AI", sf::Style::Default, windowSettings);
	sf::View playerView;
	ai = new AI();

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
		}

		sf::Time time = clock.restart();
		if (!paused)
		{
			Update(time.asSeconds());
		}
		Draw(&window, time.asSeconds());
		window.display();
	}
}

void AIGame::Update(float dt)
{


	// controller
	if (ai)
	{
		ai->m_timeUntilUpdate -= dt;

		while (ai->m_timeUntilUpdate <= 0.0f)
		{
			ai->m_timeUntilUpdate += ai->m_updateFrequency;
			if (!ai->m_currentMove.used)
			{
				if (ai->m_currentMove.swapPiece)
				{
					ai->m_currentMove.used = true;
					ai->tetris->SwitchPiece();
				}
				else
				{
					bool shouldDrop = true;
					if (ai->tetris->curpiece->maxRotations < ai->m_currentMove.numRotations)
					{
						shouldDrop = false;
						ai->tetris->RotateR();
					}
					else if (ai->tetris->curpiece->Xpos < ai->m_currentMove.col)
					{
						shouldDrop = false;
						ai->tetris->Move(1);
					}
					else if (ai->tetris->curpiece->Xpos > ai->m_currentMove.col)
					{
						shouldDrop = false;
						ai->tetris->Move(-1);
					}

					if (shouldDrop)
					{
						ai->m_currentMove.used = true;
						ai->tetris->Drop();
					}
				}
			}
		}
	} // move

	// eval
	if (ai)
	{
		if (!ai->m_initialized)
		{
			float flHeuristicWidth = ai->m_aiHeuristicRange.y - ai->m_aiHeuristicRange.x;
			ai->m_initialized = true;
			ai->m_heuristics.push_back(new AIHeuristic_AggregateHeight(-2.00 * RAND_HEURISTIC_RANGE()));
			////comp->m_heuristics.push_back(new AIHeuristic_CompletedLines(2));
			////comp->m_heuristics.push_back(new AIHeuristic_HighestCol(-2.75));
			////comp->m_heuristics.push_back(new AIHeuristic_DeepestHole(2.0 * RAND_HEURISTIC_RANGE()));
			//comp->m_heuristics.push_back(new AIHeuristic_GameLoss(-1 * RAND_HEURISTIC_RANGE()));
			ai->m_heuristics.push_back(new AIHeuristic_Holes(-5.5f));
			ai->m_heuristics.push_back(new AIHeuristic_Blockade(-.4f * RAND_HEURISTIC_RANGE()));
			ai->m_heuristics.push_back(new AIHeuristic_Bumpiness(-1.55f * RAND_HEURISTIC_RANGE()));
			//comp->m_debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Agg Height" });
			////comp->m_debugHeuristics.push_back(AIDebug{ 0.0f, "Completed Lines" });
			////comp->m_debugHeuristics.push_back(AIDebug{ 0.0f, "Highest Column" });
			////comp->m_debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Deepest Hole" });
			//comp->m_debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Game Loss" });
			//comp->m_debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Holes" });
			//comp->m_debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Blockade" });
			//comp->m_debugHeuristics.push_back(AIDebugHeuristic{ 0.0f, "Bumpiness" });
		}

		ai->m_timeSinceLastUpdate += dt;
	}

	// move
	Stack* current = ai->tetris;
	if (ai &&
		ai->CanFindMove() &&
		ai->NeedsNewMove())
	{
		ai->FindBestMove();
		DesiredMoveSet moveset = ai->GetBestMove();
		ai->SetCurrentMove(moveset);
	}
}

void AIGame::Draw(sf::RenderWindow* window, float dt)
{
	// move

	//// Debug
	Stack* current = ai->tetris;

	for (int i = 0; i < ai->m_debugHeuristics.size(); i++)
	{
		std::string textStr = ai->m_debugHeuristics[i].m_description;
		textStr += " " + std::to_string(ai->m_debugHeuristics[i].m_lastScore);
		text.setPosition(sf::Vector2f(50, (float)250 + i * 20));
		text.setString(textStr.c_str());
		window->draw(text);
	}


	// 
}

