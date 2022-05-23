#pragma once
#include "Stack.h"
#include "AIHeuristic.h"
#include "AICommon.h"

class AI
{
public:
	AI();
	~AI();
	void InitAI(float flUpdateFrequency, sf::Vector2f aiHeuristicRange);
	void Quit();
	void Calc_Best_Outcome();
	void Update();
	void FindBestMove();
	DesiredMoveSet __FindBestMove(Stack* tetrisBoard, int lookaheads, bool holdPiece);
	
	void SetUpdateFrequency(float time);
	void SetCurrentMove(DesiredMoveSet& move);
	bool NeedsNewMove();

	struct SpawnInfo
	{
		float updateFrequency;
		sf::Vector2f aiHeursticRange;
		sf::Vector2f spawnPos;
		sf::Vector2f spawnScale;

		SpawnInfo()
			: updateFrequency(00)
			, spawnPos(0, 0)
			, spawnScale(1, 1)
			, aiHeursticRange(1.0f, 1.0f)
		{

		}
	};

	sf::Vector2f m_aiSpawnPos;
	float m_flScale;
	float m_flXOffset;
	float m_flYOffset;

	bool CanFindMove() { return timeSinceLastUpdate > AI_UPDATE_RATE_SECONDS; }
	DesiredMoveSet GetBestMove();
	bool initialized;
	sf::Vector2f aiHeuristicRange;
	std::vector<AIHeuristic*> heuristics;
	std::vector<AIDebugHeuristic> debugHeuristics;
	DesiredMoveSet bestMoves[NUM_LOOKAHEAD];
	DesiredMoveSet currentMove;
	Stack* tetris;
	float timeSinceLastUpdate;
	float timeUntilUpdate;
	float updateFrequency;
	/*AIEvaluatorSystem* curSys;*/
};


/*
The key to writing an ai is to break down the decision making into
a decision between numeric values.
In order to do that a processing of the raw information needs to occur,
the result of that process should be numberic and workable with functions.
for example:
if the ai needs to decide whether a piece should be in one rotation in one place
or in a different rotation in a different place, each position should have a
value assigned to it and the decition at the bone of things should be
a simple number comparison.

Actions:
	The processing:
		- an end position type that contains three properties:
			- a rotation index in the rotation array
			- an index for the x value of the board.
			- a piece value from the colortype enum.
		- a funciton that determines and assigns the type's all possible
		current end positions from the current state (Stack)
	The AI:
		- a function that takes in as input the end position array
		and assign values to all end positions (using a nueral network)
		- a function that takes the best value of the array
	The AIGame:
		- a function that takes in an end position and places the piece
		in the position
		- a while mechanic for the game loop.
*/
