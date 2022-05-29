#include "AI.h"

AI::AI()
	: timeUntilUpdate(AI_CONTROLLER_UPDATE_FREQUENCY)
	, updateFrequency(AI_CONTROLLER_UPDATE_FREQUENCY)
	, toggleDebug(false)
{
	initialized = false;
	tetris = new Stack();
	currentMove.used = true;
	timeSinceLastUpdate = 0.0f;
}

AI::~AI()
{
	for (auto i : heuristics)
	{
		free(i);
	}
	heuristics.clear();
	for (auto i : debugHeuristics)
	{
		free(i);
	}
	debugHeuristics.clear();
	//free(bestMoves);
	delete tetris;
}

void AI::FindBestMove()
{
	if (tetris)
	{
		timeSinceLastUpdate = 0.0f;

		// Stop AI when game is lost
		bestMoves[0] = __FindBestMove(tetris, NUM_LOOKAHEAD, false);
		DesiredMoveSet heldMove;
		if (!tetris->didInsertToHold)
		{
			heldMove = __FindBestMove(tetris, NUM_LOOKAHEAD, true);
		}

		if (heldMove.score > bestMoves[0].score)
		{
			bestMoves[0] = heldMove;
		}
	}
}

DesiredMoveSet AI::__FindBestMove(Stack* tetrisBoard, int numLookaheads, bool holdPiece)
{
	DesiredMoveSet result;

	numLookaheads--;

	if (!tetris->curpiece)
	{
		return result;
	}

	if (numLookaheads == 1 && toggleDebug)
	{
		if (holdPiece)
		{
			if (tetrisBoard->held)
				std::cout << tetrisBoard->held->tetromino[0]->colorFileName << std::endl;
		}
		else
		{
			std::cout << tetrisBoard->curpiece->tetromino[0]->colorFileName << std::endl;
		}
	}


	int colMax = STACKW;
	bool xmaxset = false;

	// Try all rotations	
	int rotations = tetrisBoard->curpiece->maxRotations;
	for (int j = 0; j < rotations; j++)
	{
		xmaxset = false;
		for (int i = 0; i < colMax; i++)
		{
			// Make a copy of the board
			Stack* boardCopy = tetrisBoard->CloneStack();


			if (holdPiece)
			{
				boardCopy->Hold();
				result.swapPiece = true;
			}

			boardCopy->ResetcurpiecePositionForRotation();

			for (int numRotations = 0; numRotations < j; numRotations++)
			{
				boardCopy->curpiece->RotateTR();
			}

			boardCopy->ResetcurpiecePosition();

			boardCopy->curpiece->SetPosition(i, 0);

			if (!xmaxset)
			{
				colMax = boardCopy->GetMaximumSetXPos();
				xmaxset = true;
			}
			int colIdx = boardCopy->curpiece->Xpos;
			boardCopy->Drop(Res);
			if (*Res)
				boardCopy->resetCount++;

			// Try the current piece in a specific position
			// Try the next piece in a specific position	

			if (numLookaheads == 1 && toggleDebug)
			{
				printf("%d %d:\n", j, i);
			}
			// Try the next lookahead
			float currentScore = 0.0f;
			int index = 0;
			for (auto h : heuristics)
			{
				
				// Score the grid	
				float score = h->GetScore(tetrisBoard, boardCopy);

				if (numLookaheads == 1 && toggleDebug)
				{
					debugHeuristics.at(index)->lastScore = score;
					std::cout << debugHeuristics.at(index)->description;
					std::cout << debugHeuristics.at(index++)->lastScore << " ";
				}

				currentScore += score;
			}
			if (numLookaheads == 1 && toggleDebug)
			{
				printf("\n");
			}

			DesiredMoveSet lookaheadMove;
			if (numLookaheads > (toggleDebug) ? 1 : 0)
			{
				lookaheadMove = __FindBestMove(boardCopy, numLookaheads, false);
				currentScore += lookaheadMove.score;
			}

			if (currentScore >= result.score)
			{
				result.score = currentScore;
				result.numRotations = j;
				result.col = colIdx;
				result.used = false;

				if (numLookaheads > (toggleDebug) ? 1 : 0)
				{
					bestMoves[NUM_LOOKAHEAD - numLookaheads] = lookaheadMove;
				}
			}

			if (numLookaheads == 1 && toggleDebug)
			{
				std::cout << "\n - result.score : " << result.score << "\n";
				std::cout << " - result.numRotations : " << result.numRotations << "\n";
				std::cout << " - result.col : " << result.col << "\n";
				std::cout << " - result.swapPiece : " << result.swapPiece << "\n";
				std::cout << " - result.used : " << result.used << "\n";
			}
			delete boardCopy;
		}
		if (numLookaheads == 1 && toggleDebug)
		{
			printf("diff rot\n\n");
		}
	}
	if (numLookaheads == 1 && toggleDebug)
	{
		printf("diff piece\n\n");
	}
	return result;
}

void AI::SetUpdateFrequency(float time)
{
	updateFrequency = time;
}

void AI::SetCurrentMove(DesiredMoveSet& move)
{
	currentMove = move;
}

bool AI::NeedsNewMove()
{
	return currentMove.used;
}

DesiredMoveSet AI::GetBestMove()
{
	return bestMoves[0];
}
