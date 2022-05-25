#include "AI.h"

AI::AI()
	: timeUntilUpdate(AI_CONTROLLER_UPDATE_FREQUENCY)
	, updateFrequency(AI_CONTROLLER_UPDATE_FREQUENCY)
	, m_aiSpawnPos(0, 0)
{

	tetris = new Stack();
	currentMove.used = true; // controller comp

	m_aiSpawnPos.x = BW; // spawn comp
	m_aiSpawnPos.y = 0;

	timeSinceLastUpdate = 0.0f + rand() / (float)RAND_MAX; // eval comp
}

void AI::FindBestMove()
{
	if (tetris)
	{
		timeSinceLastUpdate = 0.0f;

		// Stop AI when game is lost
		bestMoves[0] = __FindBestMove(tetris, NUM_LOOKAHEAD, false);
		DesiredMoveSet heldMove = __FindBestMove(tetris, NUM_LOOKAHEAD, true);

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

	

	// Try all rotations	
	int rotations = tetrisBoard->curpiece->maxRotations;
	for (int j = 0; j < rotations; j++)
	{
		// Make a copy of the board
		Stack* boardCopy = tetrisBoard->CloneStack();


		if (holdPiece)
		{
			boardCopy->AIHold();
			result.swapPiece = true;
		}

		boardCopy->ResetcurpiecePositionForRotation();

		for (int numRotations = 0; numRotations < j; numRotations++)
		{
			boardCopy->curpiece->RotateTR();
		}

		boardCopy->ResetcurpiecePosition();

		int colMax = boardCopy->GetMaximumSetXPos();
		for (int i = 0; i < colMax; i++)
		{
			boardCopy->curpiece->SetPosition(i, 0);
			int colIdx = boardCopy->curpiece->Xpos;
			bool* Res = new bool();
			boardCopy->Drop(Res);
			if (*Res)
				boardCopy->resetCount++;

			// Try the current piece in a specific position
			// Try the next piece in a specific position	

			// Try the next lookahead
			float currentScore = 0.0f;
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

			if (currentScore > result.score)
			{
				result.score = currentScore;
				result.numRotations = j;
				result.col = colIdx;
				result.used = false;

				/*int index = 0;*/

				//for (auto h : heuristics)
				//{
				//	if (numLookaheads == NUM_LOOKAHEAD - 1)
				//	{
				//		float score = h->GetScore(tetrisBoard, boardCopy);
				//		// debugHeuristics[index].m_lastScore = score;
				//	}
				//	index++;
				//}

				if (numLookaheads > 0)
				{
					bestMoves[NUM_LOOKAHEAD - numLookaheads] = lookaheadMove;
				}
			}
		}
		delete boardCopy;
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

	//if (move.id != m_currentMove.id)
	//{
	//}
}

bool AI::NeedsNewMove()
{
	return currentMove.used;
}

DesiredMoveSet AI::GetBestMove()
{
	return bestMoves[0];
}
