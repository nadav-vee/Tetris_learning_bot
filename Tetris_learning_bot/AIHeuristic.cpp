#include "AIHeuristic.h"
#include "Stack.h"

float AIHeuristic_AggregateHeight::GetScore(Stack* tetrisBoard, Stack* BoardCopy)
{
	float result = 0.0f;

	for (int i = 0; i < STACKW; i++)
	{
		for (int j = 0; j < STACKH; j++)
		{
			if (BoardCopy->board[j][i]->val)
			{
				result += STACKH - j;
				break;
			}
		}
	}

	return m_scalar * result;
}

float AIHeuristic_Holes::GetScore(Stack* tetrisBoard, Stack* BoardCopy)
{
	float result = 0.0f;

	for (int i = 0; i < STACKW; i++)
	{
		bool bFoundBlock = false;
		for (int j = 0; j < STACKH; j++)
		{
			if (BoardCopy->board[j][i]->val)
			{
				bFoundBlock = true;
			}
			else if (bFoundBlock)
			{
				result++;
			}
		}
	}

	return m_scalar * result;
}

float AIHeuristic_Bumpiness::GetScore(Stack* tetrisBoard, Stack* BoardCopy)
{
	float result = 0.0f;

	int prevHeight = 0;
	for (int i = 0; i < STACKW; i++)
	{
		int height = 0;
		for (int j = 0; j < STACKH; j++)
		{
			if (BoardCopy->board[j][i]->val)
			{
				height = STACKH - j;
				break;
			}
		}

		if (i > 0)
		{
			result += abs(prevHeight - height);
		}

		prevHeight = height;
	}


	return m_scalar * result;
}

//float AIHeuristic_HighestCol::GetScore(Stack* tetrisBoard)
//{
//	float result = 0.0f;
//	int highest = 0;
//	for (int i = 0; i < tetrisBoard->m_cols; i++)
//	{
//		for (int j = 0; j < tetrisBoard->m_rows; j++)
//		{
//			if (tetrisBoard->m_grid.m_cells[i][j].m_isFilled)
//			{
//				int height = tetrisBoard->m_rows - j;
//				if (highest < height)
//				{
//					highest = height;
//					if (height + 6 > tetrisBoard->m_rows)
//					{
//						result = (float)height + 6;
//					}
//					else
//					{
//						result = (float)height;
//					}
//				}
//
//				break;
//			}
//		}
//	}
//
//	return m_scalar * result;
//}

float AIHeuristic_GameLoss::GetScore(Stack* tetrisBoard, Stack* BoardCopy)
{
	float result = 0.0f;
	if (tetrisBoard->resetCount > BoardCopy->resetCount)
	{
		result = -100000000;
	}
	return result;
}

float AIHeuristic_Blockade::GetScore(Stack* tetrisBoard, Stack* BoardCopy)
{
	float result = 0.0f;

	for (int i = 0; i < STACKW; i++)
	{
		int blockadeCount = 0;
		bool bFoundBlock = false;
		for (int j = 0; j < STACKH; j++)
		{
			if (BoardCopy->board[j][i]->val)
			{
				blockadeCount++;
				bFoundBlock = true;
			}
			else if (bFoundBlock)
			{
				result += blockadeCount;
				break;
			}
		}
	}

	return m_scalar * result;
}

