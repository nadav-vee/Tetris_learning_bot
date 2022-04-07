#include "Stack.h"


ColorsType rs()
{
	ColorsType t = (ColorsType)((rand() % 7) + 2);
	//return t;
	return ColorsType::BLUE;
}


Stack::Stack()
{
	for (int i = 0; i < STACKH; i++)
	{
		for (int j = 0; j < STACKW; j++)
		{
			board[i][j] = new Cell();
			board[i][j]->spr.setScale(SCALE, SCALE);
			board[i][j]->spr.setPosition(j * SIZE * SCALE, i * SIZE * SCALE);
		}
	} // Stack init


	curpiece = new Piece(rs());
	curpiece->MoveT(2);

	GeneratepiecesQueue(); // generating the queue

}



bool Stack::Update()
{
	if (StackColl())
	{
		return true;
	}
	if (BottomColl())
	{
		CheckScore(CopyPeiceToStack());
		TemporaryChangepieceMethode();
		return false;
	}
	curpiece->MoveTdown();
	if (BlocksColl())
	{
		curpiece->MoveTup();
		CheckScore(CopyPeiceToStack());
		TemporaryChangepieceMethode();
		return false;
	}


	return false;
}

void Stack::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < STACKH; i++)
	{
		for (int j = 0; j < STACKW; j++)
		{
			window.draw(board[i][j]->spr);
		}
	}
	// curpiece->DrawP(window);
	curpiece->DrawT(window);
	Qpieces.front()->DrawT(window);
}

int Stack::CopyPeiceToStack()
{
	int x, y;
	for (int i = 0; i < PIECESIZE; i++)
	{
		x = curpiece->tetromino[i]->x;
		y = curpiece->tetromino[i]->y;
		if (x < 10 && x >= 0 && y >= 0 && y < 20)
		{
			board[y][x]->val = true;
			board[y][x]->spr = curpiece->tetromino[i]->spr;
		}
	}

	y = 0;
	for (int i = 0; i < PIECESIZE; i++)
	{
		if (y < curpiece->tetromino[i]->y)
		{
			y = curpiece->tetromino[i]->y;
		}
	}

	return y;
}

void Stack::GameLogic(bool right, bool left, bool RotR, bool RotL, bool tochange)
{
	if (tochange)
	{
		TemporaryChangepieceMethode();
	}
	if (RotL)
	{
		curpiece->RotateTL();
		if (BlocksColl() || WallsColl())
		{
			curpiece->RotateTR();
		}
	}
	if (RotR)
	{
		curpiece->RotateTR();
		if (BlocksColl() || WallsColl())
		{
			curpiece->RotateTL();
		}
	}
	if (right)
	{
		curpiece->MoveT(1);
		if (BlocksColl() || WallsColl())
		{
			curpiece->MoveT(-1);
		}
	}
	if (left)
	{
		curpiece->MoveT(-1);
		if (BlocksColl() || WallsColl())
		{
			curpiece->MoveT(1);
		}
	}
}

bool Stack::BlocksColl()
{
	int x, y;
	for (int i = 0; i < PIECESIZE; i++)
	{
		x = curpiece->tetromino[i]->x;
		y = curpiece->tetromino[i]->y;
		if (x < 10 && x >= 0 && y >= 0 && y < 20)
		{
			if (board[y][x]->val == true)
			{
				return true;
			}
		}
	}
	return false;
}

bool Stack::WallsColl()
{
	int x;
	for (int i = 0; i < PIECESIZE; i++)
	{
		x = curpiece->tetromino[i]->x;
		if (x < 0 || x > 9)
		{
			return true;
		}
	}
	return false;
}

bool Stack::BottomColl()
{
	int y;
	for (int i = 0; i < PIECESIZE; i++)
	{
		y = curpiece->tetromino[i]->y;
		if (y + 1 > 19)
		{
			return true;
		}
	}
	return false;
}

bool Stack::StackColl()
{
	bool Lost = false;
	for (int i = 0; i < PIECESIZE; i++)
	{
		int y = curpiece->tetromino[i]->y;
		if (BlocksColl() && y < 1)
		{
			Lost = true;
		}
	}
	return Lost;
}

void Stack::CheckScore(int index)
{
	if (CheckTetris(index))
	{
		if (Combo)
		{
			Score += 400;
			Combo = false;
		}
		else
		{
			Combo = true;
		}
	}
	else
	{
		Combo = false;
	}
}

bool Stack::CheckToDel(int index)
{
	bool todel = true;
	for (int i = 0; i < STACKW; i++)
	{
		if (board[index][i]->val == false)
		{
			todel = false;
		}
	}
	if (todel)
	{
		DeleteLine(index);
	}
	return todel;
}

void Stack::DeleteLine(int index)
{
	for (int j = 0; j < STACKW ;j++)
	{
		delete board[index][j];
	}
	for (int i = index; i > 0; i--)
	{
		for (int j = 0; j < STACKW; j++)
		{
			board[i][j]->spr = board[i + 1][j]->spr;
			board[i][j]->val = board[i + 1][j]->val;
			board[i][j]->x = board[i + 1][j]->x;
			board[i][j]->y = board[i + 1][j]->y;
		}
	}
	for (int j = 0; j < STACKW; j++)
	{
		board[0][j] = new Cell();
		board[0][j]->spr.setScale(SCALE, SCALE);
		board[0][j]->spr.setPosition(j * SIZE * SCALE, 0 * SIZE * SCALE);
	}
}

bool Stack::CheckTetris(int index)
{
	bool Tet = true;
	for (int i = 3; i <= 0; i--)
	{
		if (CheckToDel(index - i))
			Score += 100;
		else
			Tet = false;
	}
	if (Tet)
		Score += 400;
	return Tet;
}

Piece* NewPiece(ColorsType rp)
{
	Piece* tmpP = new Piece(rp);
	tmpP->MoveT(10);
	return tmpP;
}


void Stack::TemporaryChangepieceMethode()
{
	delete curpiece;
	Qpieces.push(NewPiece(rs())); // rs = random shape
	Qpieces.front()->MoveT(-10);
	curpiece = Qpieces.front();
	Qpieces.pop();
}

void Stack::GeneratepiecesQueue()
{
	for (int i = 0; i < PIECELIST; i++) // generating list
	{
		int Rpiece = ((rand() % 7) + 2);
		Qpieces.push(NewPiece((ColorsType)Rpiece));
	}
}