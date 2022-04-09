#include "Stack.h"


ColorsType rs()
{
	ColorsType t = (ColorsType)((rand() % 7) + 2);
	return t;
	//return ColorsType::BLUE;
}


Stack::Stack()
{
	for (int i = 0; i < STACKH; i++)
	{
		for (int j = 0; j < STACKW; j++)
		{
			board[i][j] = new Cell();
			board[i][j]->SetPosInd(i, j);
		}
	} // Stack init

	ColorsType initcolor = rs();
	curpiece = new Piece(initcolor);
	curpieceBuffer = new Piece(initcolor);
	curpiece->MoveT(STARTINGXVAL);
	CopyPieceFunc(buff::PIECETOBUFF);

	GeneratepiecesQueue(); // generating the queue

}



bool Stack::Update(bool* toRes)
{
	int score;
	if (StackColl())
	{
		*toRes = true;
		return true;
	}
	if (BottomColl())
	{
		CheckScore(CopyPeiceToStack());
		TemporaryChangepieceMethode();
		return true;
	}
	curpiece->MoveTdown();
	curpieceBuffer->MoveTdown();
	if (BlocksColl())
	{
		curpiece->MoveTup();
		curpieceBuffer->MoveTup();
		CheckScore(CopyPeiceToStack());
		TemporaryChangepieceMethode();
		return true;
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

void Stack::GameLogic(bool right, bool left, bool RotR, bool RotL, bool tochange, bool dropp, bool fasterdown)
{
	bool* FaketoRes = (bool*)malloc(sizeof(bool));
	*FaketoRes = false;
	if (tochange)
	{
		TemporaryChangepieceMethode();
	}
	if (RotL)
	{
		curpiece->RotateTL();
		if (BlocksColl() || WallsColl())
		{
			CopyPieceFunc(buff::BUFFTOPIECE);
		}
	}
	if (RotR)
	{
		curpiece->RotateTR();
		if (BlocksColl() || WallsColl())
		{
			CopyPieceFunc(buff::BUFFTOPIECE);
		}
	}
	if (right)
	{
		curpiece->MoveT(1);
		if (BlocksColl() || WallsColl())
		{
			CopyPieceFunc(buff::BUFFTOPIECE);
		}
	}
	if (left)
	{
		curpiece->MoveT(-1);
		if (BlocksColl() || WallsColl())
		{
			CopyPieceFunc(buff::BUFFTOPIECE);
		}
	}
	if (dropp)
	{
		bool dropping = true;
		while (dropping)
		{
			if (Update(FaketoRes))
			{
				dropping = false;
			}
		}
	}
	if (fasterdown)
	{
		Update(FaketoRes);
	}
	CopyPieceFunc(buff::PIECETOBUFF);
	free(FaketoRes);
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
	for (int j = 0; j < STACKW; j++)
	{
		delete board[index][j];
	}
	for (int i = index; i > 0; i--)
	{
		for (int j = 0; j < STACKW; j++)
		{
			if (i == index)
			{
				board[i][j] = new Cell();
			}
			board[i][j]->spr.setTexture(*board[i - 1][j]->spr.getTexture());
			board[i][j]->SetPosInd(i, j);
			board[i][j]->val = board[i - 1][j]->val;
			board[i][j]->x = board[i - 1][j]->x;
			board[i][j]->y = board[i - 1][j]->y;
		}
	}
	for (int j = 0; j < STACKW; j++)
	{
		board[0][j] = new Cell();
		board[0][j]->SetPosInd(0,j);
	}
}

bool Stack::CheckTetris(int index)
{
	bool Tet = true;
	if (index - 3 > 0)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (CheckToDel(index - i))
				Score += 100;
			else
				Tet = false;
		}
	}
	else
	{
		for (int i = index; i >= 0; i--)
		{
			if (CheckToDel(index - i))
				Score += 100;
		}
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
	delete curpieceBuffer;
	Qpieces.push(NewPiece(rs())); // rs = random shape
	Qpieces.front()->MoveT(-6);
	curpiece = Qpieces.front();
	ColorsType buffcolor = curpiece->getColorPiece();
	curpieceBuffer = new Piece(buffcolor);
	CopyPieceFunc(buff::PIECETOBUFF);
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

void Stack::CopyPieceFunc(enum buff buf)
{
	if (buf)
	{
		for (int i = 0; i < PIECESIZE; i++)
		{
			curpieceBuffer->tetromino[i]->spr = curpiece->tetromino[i]->spr;
			curpieceBuffer->tetromino[i]->val = curpiece->tetromino[i]->val;
			curpieceBuffer->tetromino[i]->x = curpiece->tetromino[i]->x;
			curpieceBuffer->tetromino[i]->y = curpiece->tetromino[i]->y;
		}
	}
	else
	{
		for (int i = 0; i < PIECESIZE; i++)
		{
			curpiece->tetromino[i]->spr = curpieceBuffer->tetromino[i]->spr;
			curpiece->tetromino[i]->val = curpieceBuffer->tetromino[i]->val;
			curpiece->tetromino[i]->x = curpieceBuffer->tetromino[i]->x;
			curpiece->tetromino[i]->y = curpieceBuffer->tetromino[i]->y;
		}
	}
}
