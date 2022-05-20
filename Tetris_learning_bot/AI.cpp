#include "AI.h"

AI::AI()
	: m_timeUntilUpdate(AI_CONTROLLER_UPDATE_FREQUENCY)
	, m_updateFrequency(AI_CONTROLLER_UPDATE_FREQUENCY)
	, m_aiSpawnPos(0, 0)
{

	tetris = new Stack();
	m_currentMove.used = true; // controller comp

	m_aiSpawnPos.x = BW; // spawn comp
	m_aiSpawnPos.y = 0;

	m_flScale = 0.5f;
	m_flXOffset = BW * m_flScale;
	m_flYOffset = BH * m_flScale + 50;

	m_timeSinceLastUpdate = 0.0f + rand() / (float)RAND_MAX; // eval comp
}

void AI::FindBestMove()
{
	if (tetris)
	{
		m_timeSinceLastUpdate = 0.0f;

		// Stop AI when game is lost
		m_bestMoves[0] = __FindBestMove(tetris, NUM_LOOKAHEAD, false);
		DesiredMoveSet heldMove = __FindBestMove(tetris, NUM_LOOKAHEAD, true);

		if (heldMove.score > m_bestMoves[0].score)
		{
			m_bestMoves[0] = heldMove;
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

	for (int i = 0; i < STACKW; i++)
	{
		// Try all rotations	
		int rotations = tetrisBoard->curpiece->maxRotations;
		for (int j = 0; j < rotations; j++)
		{
			// Make a copy of the board
			Stack* boardCopy = tetrisBoard->CloneStack();

			if (holdPiece)
			{
				boardCopy->Hold();
				result.swapPiece = true;
			}

			for (int numRotations = 0; numRotations < j; numRotations++)
			{
				boardCopy->curpiece->RotateTR();
			}
			boardCopy->ResetcurpiecePosition();
			boardCopy->curpiece->SetPosition(i, 0);
			int colIdx = INT_MAX;
			for (int i = 0; i < PIECESIZE; i++)
			{
				if (colIdx > tetrisBoard->curpiece->tetromino[i]->x)
					colIdx = tetrisBoard->curpiece->tetromino[i]->x;
			}
			boardCopy->Drop();

			// Try the current piece in a specific position
			// Try the next piece in a specific position	

			// Try the next lookahead
			float currentScore = 0.0f;
			for (auto h : m_heuristics)
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

				int index = 0;

				for (auto h : m_heuristics)
				{
					if (numLookaheads == NUM_LOOKAHEAD - 1)
					{
						float score = h->GetScore(tetrisBoard, boardCopy);
						m_debugHeuristics[index].m_lastScore = score;
					}
					index++;
				}

				if (numLookaheads > 0)
				{
					m_bestMoves[NUM_LOOKAHEAD - numLookaheads] = lookaheadMove;
				}
			}
		}
	}

	return result;
}

void AI::SetUpdateFrequency(float time)
{
	m_updateFrequency = time;
}

void AI::SetCurrentMove(DesiredMoveSet& move)
{
	if (move.id != m_currentMove.id)
	{
		m_currentMove = move;
	}
}

bool AI::NeedsNewMove()
{
	return m_currentMove.used;
}

DesiredMoveSet AI::GetBestMove()
{
	return m_bestMoves[0];
}
