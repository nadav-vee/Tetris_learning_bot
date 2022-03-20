#include "Stack.h"


ColorsType rs()
{
	ColorsType t = (ColorsType)((rand() % 7) + 2);
	return t;
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
		CopyPeiceToStack();
		TemporaryChangepieceMethode();
		return false;
	}
	curpiece->MoveTdown();
	if (BlocksColl())
	{
		curpiece->MoveTup();
		CopyPeiceToStack();
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

void Stack::CopyPeiceToStack()
{
	int x, y;
	for (int i = 0; i < PIECESIZE; i++)
	{
		x = curpiece->tetromino[i]->x;
		y = curpiece->tetromino[i]->y;
		board[y][x]->val = true;
		board[y][x]->spr = curpiece->tetromino[i]->spr;
	}
}

void Stack::GameLogic(bool right, bool left, bool RotR, bool RotL)
{
	if (RotL)
	{
		curpiece->RotateTL();
		if (BlocksColl())
		{
			curpiece->RotateTR();
		}
	}
	if (RotR)
	{
		curpiece->RotateTR();
		if (BlocksColl())
		{
			curpiece->RotateTL();
		}
	}
	if (right)
	{
		curpiece->MoveT(1);
		if (BlocksColl())
		{
			curpiece->MoveT(-1);
		}
	}
	if (left)
	{
		curpiece->MoveT(-1);
		if (BlocksColl())
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
		if (board[y][x]->val == true)
		{
			return true;
		}
	}
	return false;
}

bool Stack::WallsColl()
{
	int x, y;
	for (int i = 0; i < PIECESIZE; i++)
	{
		x = curpiece->tetromino[i]->x;
		y = curpiece->tetromino[i]->y;
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
		if (y+1 > 19)
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