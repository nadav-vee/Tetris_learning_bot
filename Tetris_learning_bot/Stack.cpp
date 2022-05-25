#include "Stack.h"


/// <summary>
///		a simple random for the piece queue
/// </summary>
ColorsType rs()
{
	return (ColorsType)((rand() % 7) + 2);
}

/// <summary>
///		a constructor of the Stack type the main structure of the tetris game
/// </summary>
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

	Color = rs();
	curpiece = new Piece(Color);
	curpieceBuffer = new Piece(Color);
	shadow = new Piece(Color);
	shadow->Shadow();
	CopyPieceFunc(buff::PIECETOBUFF);

	GeneratepiecesQueue(); // generating the queue

}
/// <summary>
///		a destructor of the Stack type which is the main class of the tetris game
/// </summary>
Stack::~Stack()
{
	delete curpiece;
	delete curpieceBuffer;
	delete held;
	delete heldBuffer;
	delete shadow;
	int Qsize = Qpieces.size();
	for (int i = 0; i < Qsize; i++)
	{
		Piece* toDel = Qpieces.front();
		Qpieces.pop();
		delete toDel;
	}
	for (int i = 0; i < STACKH; i++)
	{
		for (int j = 0; j < STACKW; j++)
		{
			delete board[i][j];
		}
	}
}


/// <summary>
///		an update method that consetrates all collision checking and buffer handling
///		the function also handles the piece "shadow"
/// </summary>
/// <param name="toRes">
///		a call by referecnce, bool pointer which represents wheather the game needs 
///		to be reset
/// </param>
/// <returns>
///		the function returns true when the piece cannot move anymore
/// </returns>
bool Stack::Update(bool* toRes)
{
	if (StackColl())
	{
		*toRes = true;
		return true;
	}
	if (BottomColl())
	{
		CheckScore(CopyPeiceToStack());
		SwitchPiece();
		return true;
	}
	curpiece->MoveTdown();
	curpieceBuffer->MoveTdown();
	if (BlocksColl())
	{
		curpiece->MoveTup();
		curpieceBuffer->MoveTup();
		CheckScore(CopyPeiceToStack());
		SwitchPiece();
		return true;
	}
	if (IsShadowColl())
		toggleShadow = false;

	return false;
}

/// <summary>
///		a draw function, draw
/// </summary>
/// <param name="window">
///		
/// </param>
void Stack::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < STACKH; i++)
	{
		for (int j = 0; j < STACKW; j++)
		{
			window.draw(board[i][j]->spr);
		}
	}
	curpiece->DrawT(window);
	Qpieces.front()->MoveT(11);
	Qpieces.front()->DrawT(window);
	Qpieces.front()->MoveT(-11);
	if (toggleShadow)
	{
		shadow->DrawT(window);
	}
	if (isHolding)
	{
		held->DrawT(window);
	}
}

/// <summary>
///		a function that switches the current piece using the queue
/// </summary>
void Stack::SwitchPiece()
{
	delete curpiece;
	delete curpieceBuffer;
	delete shadow;
	Qpieces.push(NewPiece(rs())); // rs = random shape
	curpiece = Qpieces.front();
	Color = curpiece->getColorPiece();
	curpieceBuffer = new Piece(Color);
	CopyPieceFunc(buff::PIECETOBUFF);
	shadow = new Piece(Color);
	SetShadow();
	Qpieces.pop();
	didInsertToHold = false;
}

/// <summary>
///		a function that generates a queue for the next 5 pieces.
/// </summary>
void Stack::GeneratepiecesQueue()
{
	for (int i = 0; i < PIECELIST; i++) // generating list
	{
		int Rpiece = ((rand() % 7) + 2);
		Qpieces.push(NewPiece((ColorsType)Rpiece));
	}
}


/// <summary>
///		a function that sets the current piece in the stack after the
/// </summary>
/// <returns></returns>
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
			board[y][x]->SetTex(curpiece->tetromino[i]->colorFileName);
			board[y][x]->x = x;
			board[y][x]->y = y;
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


/// <summary>
///		
/// </summary>
/// <param name="right">
///		
///	</param>
/// <param name="left">
///		
/// </param>
/// <param name="RotR">
///		
///	</param>
/// <param name="RotL">
///		
/// </param>
/// <param name="tochange">
///		
/// </param>
/// <param name="dropp">
///		
///	</param>
/// <param name="fasterdown">
///		
///	</param>
/// <param name="hold">
///		
/// </param>
void Stack::GameLogic(bool right, bool left, bool RotR,
	bool RotL, bool tochange, bool dropp, bool fasterdown, bool hold)
{
	bool* FaketoRes = (bool*)malloc(sizeof(bool));
	*FaketoRes = false;
	if (tochange)
	{
		SwitchPiece();
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
		shadow->MoveT(1);
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
		toggleShadow = false;
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
	if (hold)
	{
		if (!didInsertToHold)
		{
			Hold();
		}
	}
	CopyPieceFunc(buff::PIECETOBUFF);
	CopyPieceFunc(buff::PIECETOSHADOW);
	SetShadow();
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
	if (y < 0)
	{
		y = 0;
		for (int i = 0; i < STACKW; i++)
		{
			if (board[y][i]->val == true)
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


/// <summary>
///		handles two situations:
///			1. when there's a held piece it checks whether the holding logic is currect
///			and if it is currect it switches the pieces
///			2. when there's no held piece it just places the piece in hold
/// </summary>
void Stack::Hold()
{
	if (isHolding)
	{
		CopyPieceFunc(buff::HELDTOHBUFF);
		CopyPieceFunc(buff::PIECETOHELD);
		CopyPieceFunc(buff::HBUFFTOPIECE);
		held->SetHeldPosition();
		curpiece->SetStartingPos();
	}
	else
	{
		held = new Piece(ColorsType::GREY);
		heldBuffer = new Piece(ColorsType::GREY);
		CopyPieceFunc(buff::PIECETOHELD);
		CopyPieceFunc(buff::HELDTOHBUFF);
		held->SetHeldPosition();
		isHolding = true;
		AISwitchPiece();
	}
	didInsertToHold = true;
}


/// <summary>
///		uses existing logic from the update and the buffer methods to set 
///		a shadow for the piece
/// </summary>
void Stack::SetShadow()
{
	CopyPieceFunc(buff::PIECETOSHADOW);
	bool* FaketoRes = (bool*)malloc(sizeof(bool));
	if (FaketoRes != NULL)
		*FaketoRes = false;
	bool dropping = true;
	while (dropping)
	{
		if (ShadowUpdate(FaketoRes))
		{
			dropping = false;
		}
	}
	if (*FaketoRes)
	{
		toggleShadow = false;
	}
	else
	{
		toggleShadow = true;
	}
	free(FaketoRes);
	if (IsShadowColl())
		toggleShadow = false;
}



bool Stack::IsShadowColl()
{
	bool col = false;

	for (int c = 0; c < PIECESIZE; c++)
	{
		for (int s = 0; s < PIECESIZE; s++)
		{
			if (curpiece->tetromino[c]->x == shadow->tetromino[s]->x
				&& curpiece->tetromino[c]->y == shadow->tetromino[s]->y)
			{
				col = true;
			}
		}
	}
	return col;
}

bool Stack::ShadowUpdate(bool* toRes)
{
	if (ShadowStackColl())
	{
		*toRes = true;
		return true;
	}
	if (ShadowBottomColl())
	{
		return true;
	}
	shadow->MoveTdown();
	if (ShadowBlocksColl())
	{
		shadow->MoveTup();
		return true;
	}
	return false;
}

bool Stack::ShadowStackColl()
{
	bool Lost = false;
	for (int i = 0; i < PIECESIZE; i++)
	{
		int y = shadow->tetromino[i]->y;
		if (BlocksColl() && y < 1)
		{
			Lost = true;
		}
	}
	return Lost;
}

bool Stack::ShadowBlocksColl()
{
	int x, y;
	for (int i = 0; i < PIECESIZE; i++)
	{
		x = shadow->tetromino[i]->x;
		y = shadow->tetromino[i]->y;
		if (x < 10 && x >= 0 && y >= 0 && y < 20)
		{
			if (board[y][x]->val == true)
			{
				return true;
			}
		}
	}
	if (y < 0)
	{
		y = 0;
		for (int i = 0; i < STACKW; i++)
		{
			if (board[y][i]->val == true)
			{
				return true;
			}
		}
	}
	return false;
}

bool Stack::ShadowBottomColl()
{
	int y;
	for (int i = 0; i < PIECESIZE; i++)
	{
		y = shadow->tetromino[i]->y;
		if (y + 1 > 19)
		{
			return true;
		}
	}
	return false;
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
		board[0][j]->SetPosInd(0, j);
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

void Stack::Move(int x)
{
	curpiece->MoveT(x);
	SetShadow();
}

void Stack::RotateL()
{
	curpiece->RotateTL();
}

void Stack::RotateR()
{
	curpiece->RotateTR();
	if (BlocksColl() || WallsColl())
	{
		CopyPieceFunc(buff::BUFFTOPIECE);
	}
}

void Stack::Drop(bool* restart)
{
	if (StackColl())
	{
		*restart = true;
		return;
	}
	if (BottomColl())
	{
		CheckScore(CopyPeiceToStack());
		return;
	}
	curpiece->MoveTdown();
	curpieceBuffer->MoveTdown();
	if (BlocksColl())
	{
		curpiece->MoveTup();
		curpieceBuffer->MoveTup();
		CheckScore(CopyPeiceToStack());
		return;
	}
	Drop(restart);
}

void Stack::AIHold()
{
	if (isHolding)
	{
		CopyPieceFunc(buff::HELDTOHBUFF);
		CopyPieceFunc(buff::PIECETOHELD);
		CopyPieceFunc(buff::HBUFFTOPIECE);
		curpiece->UpdatePos();
		held->SetHeldPosition();
		heldBuffer->SetHeldPosition();
	}
	else
	{
		held = new Piece(ColorsType::GREY);
		heldBuffer = new Piece(ColorsType::GREY);
		CopyPieceFunc(buff::PIECETOHELD);
		CopyPieceFunc(buff::HELDTOHBUFF);
		held->SetHeldPosition();
		isHolding = true;
		AISwitchPiece();
	}
	didInsertToHold = true;
}

void Stack::NewPieceAndDrop(bool* restart)
{
	Drop(restart);
	AISwitchPiece();
}

Stack* Stack::CloneStack()
{
	Stack* toret = new Stack();
	for (int i = 0; i < STACKH; i++)
	{
		for (int j = 0; j < STACKW; j++)
		{
			toret->board[i][j]->SetTex(board[i][j]->colorFileName);
			toret->board[i][j]->val = board[i][j]->val;
			toret->board[i][j]->x = board[i][j]->x;
			toret->board[i][j]->y = board[i][j]->y;
		}
	}
	if (held)
	{
		toret->held = new Piece(ColorsType::BLUE);
	}
	if (heldBuffer)
	{
		toret->heldBuffer = new Piece(ColorsType::BLUE);
	}
	toret->Qpieces.empty();
	Piece* tmpPiece;
	for (int i = 0; i < Qpieces.size(); i++)
	{
		tmpPiece = new Piece(ColorsType::BLUE);
		Qpieces.push(Qpieces.front());
		for (int j = 0; j < PIECESIZE; j++)
		{
			tmpPiece->tetromino[j]->SetTex(Qpieces.front()->tetromino[j]->colorFileName);
			tmpPiece->tetromino[j]->val = Qpieces.front()->tetromino[j]->val;
			tmpPiece->tetromino[j]->x = Qpieces.front()->tetromino[j]->x;
			tmpPiece->tetromino[j]->y = Qpieces.front()->tetromino[j]->y;
		}
		tmpPiece->maxRotations = Qpieces.front()->maxRotations;
		toret->Qpieces.push(tmpPiece);
		Qpieces.pop();
	}
	for (int j = 0; j < PIECESIZE; j++)
	{
		toret->curpiece->tetromino[j]->SetTex(curpiece->tetromino[j]->colorFileName);
		toret->curpiece->tetromino[j]->val = curpiece->tetromino[j]->val;
		toret->curpiece->tetromino[j]->x = curpiece->tetromino[j]->x;
		toret->curpiece->tetromino[j]->y = curpiece->tetromino[j]->y;
		toret->curpiece->maxRotations = curpiece->maxRotations;

		if (held)
		{
			toret->held->tetromino[j]->SetTex(held->tetromino[j]->colorFileName);
			toret->held->tetromino[j]->val = held->tetromino[j]->val;
			toret->held->tetromino[j]->x = held->tetromino[j]->x;
			toret->held->tetromino[j]->y = held->tetromino[j]->y;
			toret->held->maxRotations = held->maxRotations;
		}

		if (heldBuffer)
		{
			toret->heldBuffer->tetromino[j]->SetTex(heldBuffer->tetromino[j]->colorFileName);
			toret->heldBuffer->tetromino[j]->val = heldBuffer->tetromino[j]->val;
			toret->heldBuffer->tetromino[j]->x = heldBuffer->tetromino[j]->x;
			toret->heldBuffer->tetromino[j]->y = heldBuffer->tetromino[j]->y;
			toret->heldBuffer->maxRotations = heldBuffer->maxRotations;
		}

		toret->shadow->tetromino[j]->SetTex(shadow->tetromino[j]->colorFileName);
		toret->shadow->tetromino[j]->val = shadow->tetromino[j]->val;
		toret->shadow->tetromino[j]->x = shadow->tetromino[j]->x;
		toret->shadow->tetromino[j]->y = shadow->tetromino[j]->y;
		toret->shadow->maxRotations = shadow->maxRotations;

		toret->curpieceBuffer->tetromino[j]->SetTex(curpieceBuffer->tetromino[j]->colorFileName);
		toret->curpieceBuffer->tetromino[j]->val = curpieceBuffer->tetromino[j]->val;
		toret->curpieceBuffer->tetromino[j]->x = curpieceBuffer->tetromino[j]->x;
		toret->curpieceBuffer->tetromino[j]->y = curpieceBuffer->tetromino[j]->y;
		toret->curpieceBuffer->maxRotations = curpieceBuffer->maxRotations;
	}
	toret->Color = Color;
	toret->Combo = Combo;
	toret->didInsertToHold = didInsertToHold;
	toret->Score = Score;
	toret->toggleShadow = toggleShadow;

	return toret;
}

void Stack::ResetcurpiecePosition()
{
	curpiece->Xpos = 0;
	curpiece->Ypos = 0;
	curpiece->ResetPos();
}

void Stack::ResetcurpiecePositionForRotation()
{
	curpiece->Xpos = 4;
	curpiece->Ypos = 1;
	curpiece->ResetPos();
}

int Stack::GetMaximumSetXPos()
{
	int maxXPos = STACKW;
	int max = 0, min = INT_MAX, x;
	for (int i = 0; i < PIECESIZE; i++)
	{
		x = curpiece->tetromino[i]->x;
		if (x > max) max = x;
		if (x <= min) min = x;
	}
	min--;
	maxXPos -= (max - min);
	return maxXPos;
}

void Stack::AISwitchPiece()
{
	delete curpiece;
	delete curpieceBuffer;
	delete shadow;
	Qpieces.push(NewPiece(rs())); // rs = random shape
	curpiece = Qpieces.front();
	Color = curpiece->getColorPiece();
	curpieceBuffer = new Piece(Color);
	shadow = new Piece(Color);
	ResetcurpiecePosition();
	CopyPieceFunc(buff::PIECETOBUFF);
	Qpieces.pop();
	didInsertToHold = false;
}

bool Stack::CeilingColl()
{
	for (int i = 0; i < PIECESIZE; i++)
	{
		if (curpiece->tetromino[i]->y < 0)
		{
			return true;
		}
	}

	return false;
}

Piece* Stack::NewPiece(ColorsType rp)
{
	Piece* tmpP = new Piece(rp);
	return tmpP;
}


void Stack::CopyPieceFunc(enum buff buf)
{
	Color = curpiece->getColorPiece();
	switch (buf)
	{
	case BUFFTOPIECE:
		for (int i = 0; i < PIECESIZE; i++)
		{
			curpiece->setColorPiece(curpieceBuffer->getColorPiece());
			curpiece->tetromino[i]->SetTex(curpieceBuffer->tetromino[i]->colorFileName);
			curpiece->tetromino[i]->x = curpieceBuffer->tetromino[i]->x;
			curpiece->tetromino[i]->y = curpieceBuffer->tetromino[i]->y;
		}
		break;
	case PIECETOBUFF:
		for (int i = 0; i < PIECESIZE; i++)
		{
			curpieceBuffer->setColorPiece(curpiece->getColorPiece());
			curpieceBuffer->tetromino[i]->SetTex(curpiece->tetromino[i]->colorFileName);
			curpieceBuffer->tetromino[i]->val = curpiece->tetromino[i]->val;
			curpieceBuffer->tetromino[i]->x = curpiece->tetromino[i]->x;
			curpieceBuffer->tetromino[i]->y = curpiece->tetromino[i]->y;
		}
		break;
	case PIECETOHELD:
		for (int i = 0; i < PIECESIZE; i++)
		{
			held->setColorPiece(Color);
			held->tetromino[i]->SetTex(curpiece->tetromino[i]->colorFileName);
			held->tetromino[i]->val = curpiece->tetromino[i]->val;
			held->tetromino[i]->x = curpiece->tetromino[i]->x;
			held->tetromino[i]->y = curpiece->tetromino[i]->y;
		}
		break;
	case HELDTOHBUFF:
		for (int i = 0; i < PIECESIZE; i++)
		{
			heldBuffer->setColorPiece(held->getColorPiece());
			heldBuffer->tetromino[i]->SetTex(held->tetromino[i]->colorFileName);
			heldBuffer->tetromino[i]->val = held->tetromino[i]->val;
			heldBuffer->tetromino[i]->x = held->tetromino[i]->x;
			heldBuffer->tetromino[i]->y = held->tetromino[i]->y;
		}
		break;
	case HBUFFTOPIECE:
		for (int i = 0; i < PIECESIZE; i++)
		{
			curpiece->setColorPiece(heldBuffer->getColorPiece());
			curpiece->tetromino[i]->SetTex(heldBuffer->tetromino[i]->colorFileName);
			curpiece->tetromino[i]->val = heldBuffer->tetromino[i]->val;
			curpiece->tetromino[i]->x = heldBuffer->tetromino[i]->x;
			curpiece->tetromino[i]->y = heldBuffer->tetromino[i]->y;
		}
		break;
	case PIECETOSHADOW:
		auto shadowtex = NOpiece;
		switch (Color)
		{
		case BLUE:
			shadowtex = SHADOWIpiece;
			break;
		case GREEN:
			shadowtex = SHADOWSpiece;
			break;
		case ORANGE:
			shadowtex = SHADOWLpiece;
			break;
		case PINK:
			shadowtex = SHADOWJpiece;
			break;
		case PURPLE:
			shadowtex = SHADOWTpiece;
			break;
		case RED:
			shadowtex = SHADOWZpiece;
			break;
		case YELLOW:
			shadowtex = SHADOWOpiece;
			break;
		default:
			shadowtex = Shadowpiece;
			break;
		}
		for (int i = 0; i < PIECESIZE; i++)
		{
			shadow->tetromino[i]->val = curpiece->tetromino[i]->val;
			shadow->tetromino[i]->x = curpiece->tetromino[i]->x;
			shadow->tetromino[i]->y = curpiece->tetromino[i]->y;
			shadow->tetromino[i]->SetTex(shadowtex);
		}
		break;
	}
}
