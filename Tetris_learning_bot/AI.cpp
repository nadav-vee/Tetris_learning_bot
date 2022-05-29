#include "AI.h"

AI::AI()
	: timeUntilUpdate(AI_CONTROLLER_UPDATE_FREQUENCY)
	, updateFrequency(AI_CONTROLLER_UPDATE_FREQUENCY)
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

			// Try the next lookahead
			float currentScore = 0.0f;
			int index = 0;
			for (auto h : heuristics)
			{
				
				// Score the grid	
				float score = h->GetScore(tetrisBoard, boardCopy);

				currentScore += score;
			}

			DesiredMoveSet lookaheadMove;
			if (numLookaheads > 0)
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

				if (numLookaheads > 0)
				{
					bestMoves[NUM_LOOKAHEAD - numLookaheads] = lookaheadMove;
				}
			}
			delete boardCopy;
		}
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
