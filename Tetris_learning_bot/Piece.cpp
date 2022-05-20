#include "Piece.h"


Piece::Piece(enum ColorsType piecetype)
	: maxRotations(4),
	pivot(1),
	curPieceColor(piecetype)
{
	for (int i = 0; i < PIECESIZE; i++)
	{
		tetromino[i] = new Cell();
		tetromino[i]->val = true;
		//tetromino[i]->y = 0-PLH;
	}
	std::string filet;
	switch (piecetype)
	{
	case ColorsType::SHADOW:
		break;
	case ColorsType::GREY:
		break;
	case ColorsType::BLUE:
		filet = Ipiece;
		pivot = 2;
		maxRotations = 2;
		tetromino[0]->SetTex(filet);
		tetromino[1]->SetTex(filet);
		tetromino[2]->SetTex(filet);
		tetromino[3]->SetTex(filet);
		tetromino[0]->x = 1;	// the blue I piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 1;	// 0 1 0 0
		tetromino[1]->y = 1;	// 0 1 0 0
		tetromino[2]->x = 1;	// 0 1 0 0
		tetromino[2]->y = 2;	// 0 1 0 0
		tetromino[3]->x = 1;	//
		tetromino[3]->y = 3;	//
		break;
	case ColorsType::GREEN:
		filet = Spiece;
		maxRotations = 2;
		tetromino[0]->SetTex(filet);
		tetromino[1]->SetTex(filet);
		tetromino[2]->SetTex(filet);
		tetromino[3]->SetTex(filet);
		tetromino[0]->x = 1;	// the green S piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 1;	// 
		tetromino[1]->y = 1;	// 0 1 1
		tetromino[2]->x = 0;	// 1 1 0
		tetromino[2]->y = 1;	// 0 0 0
		tetromino[3]->x = 2;	//
		tetromino[3]->y = 0;	//
		break;
	case ColorsType::ORANGE:
		filet = Lpiece;
		tetromino[0]->SetTex(filet);
		tetromino[1]->SetTex(filet);
		tetromino[2]->SetTex(filet);
		tetromino[3]->SetTex(filet);
		tetromino[0]->x = 1;    // the orange L piece
		tetromino[0]->y = 0;    // 
		tetromino[1]->x = 1;    // 0 1 0
		tetromino[1]->y = 1;    // 0 1 0
		tetromino[2]->x = 1;    // 0 1 1
		tetromino[2]->y = 2;    // 
		tetromino[3]->x = 2;    //
		tetromino[3]->y = 2;    //
		break;
	case ColorsType::PINK:
		filet = Jpiece;
		tetromino[0]->SetTex(filet);
		tetromino[1]->SetTex(filet);
		tetromino[2]->SetTex(filet);
		tetromino[3]->SetTex(filet);
		tetromino[0]->x = 1;	// the pink J piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 1;	// 0 1 0
		tetromino[1]->y = 1;	// 0 1 0
		tetromino[2]->x = 1;	// 1 1 0
		tetromino[2]->y = 2;	// 
		tetromino[3]->x = 0;	//
		tetromino[3]->y = 2;	//
		break;
	case ColorsType::PURPLE:
		filet = Tpiece;
		tetromino[0]->SetTex(filet);
		tetromino[1]->SetTex(filet);
		tetromino[2]->SetTex(filet);
		tetromino[3]->SetTex(filet);
		tetromino[0]->x = 1;	// the purple T piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 1;	//
		tetromino[1]->y = 1;	// 0 1 0
		tetromino[2]->x = 0;	// 1 1 1
		tetromino[2]->y = 1;	// 0 0 0
		tetromino[3]->x = 2;	//
		tetromino[3]->y = 1;	//
		break;
	case ColorsType::RED:
		filet = Zpiece;
		maxRotations = 2;
		tetromino[0]->SetTex(filet);
		tetromino[1]->SetTex(filet);
		tetromino[2]->SetTex(filet);
		tetromino[3]->SetTex(filet);
		tetromino[0]->x = 0;	// the red Z piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 1;	//
		tetromino[1]->y = 1;	// 1 1 0
		tetromino[2]->x = 1;	// 0 1 1
		tetromino[2]->y = 0;	// 0 0 0
		tetromino[3]->x = 2;	//
		tetromino[3]->y = 1;	//
		break;
	case ColorsType::YELLOW:
		pivot = -1;
		filet = Opiece;
		maxRotations = 1;
		tetromino[0]->SetTex(filet);
		tetromino[1]->SetTex(filet);
		tetromino[2]->SetTex(filet);
		tetromino[3]->SetTex(filet);
		tetromino[0]->x = 1;	// the yellow O piece
		tetromino[0]->y = 1;	// 
		tetromino[1]->x = 2;	// 0 0 0 0
		tetromino[1]->y = 1;	// 0 1 1 0
		tetromino[2]->x = 1;	// 0 1 1 0
		tetromino[2]->y = 2;	// 0 0 0 0
		tetromino[3]->x = 2;	//
		tetromino[3]->y = 2;	//
		break;
	default:
		break;
	}
	for (int i = 0; i < 4; i++)
	{
		tetromino[i]->y -= 4;
	}
	UpdateTetrominoPos();
}

Piece::~Piece()
{
	for (int j = 0; j < PIECESIZE; j++)
	{
		if (tetromino[j])
			delete tetromino[j];
		tetromino[j] = NULL;
	}
}

ColorsType Piece::getColorPiece()
{
	return curPieceColor;
}

void Piece::setColorPiece(ColorsType color)
{
	curPieceColor = color;
}

void Piece::SetPosition(int x, int y)
{
	MoveT(x);
	for (int i = 0; i < (y + 4); i++)
	{
		MoveTdown();
	}
	Xpos = GetMinXFromTet();
}

void Piece::SetStartingPos()
{
	ResetPos();
	MoveT(STARTINGXVAL);
	Xpos = GetMinXFromTet();
}

void Piece::SetNextPosition()
{
	ResetPos();
	MoveT(NEXTPXVAL);
	MoveTdown();
	Xpos = GetMinXFromTet();
}

void Piece::SetHeldPosition()
{
	SetNextPosition();
	for (int i = 0; i < PIECESIZE; i++)
	{
		tetromino[i]->y += HELDPYVAL;
	}
	UpdateTetrominoPos();
}

int Piece::GetMinXFromTet()
{
	int x = INT_MAX;
	for (int i = 0; i < PIECESIZE; i++)
	{
		if (x < tetromino[i]->x) x = tetromino[i]->x;
	}
	return x;
}

void Piece::ResetPos()
{
	switch (curPieceColor)
	{
	case ColorsType::SHADOW:
		break;
	case ColorsType::GREY:
		break;
	case ColorsType::BLUE:
		tetromino[0]->x = 0;	// the blue I piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 0;	// 1 0 0 0
		tetromino[1]->y = 1;	// 1 0 0 0
		tetromino[2]->x = 0;	// 1 0 0 0 
		tetromino[2]->y = 2;	// 1 0 0 0
		tetromino[3]->x = 0;	//
		tetromino[3]->y = 3;	//
		break;
	case ColorsType::GREEN:
		tetromino[0]->x = 1;	// the green S piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 1;	// 
		tetromino[1]->y = 1;	// 0 1 1
		tetromino[2]->x = 0;	// 1 1 0
		tetromino[2]->y = 1;	// 0 0 0
		tetromino[3]->x = 2;	//
		tetromino[3]->y = 0;	//
		break;
	case ColorsType::ORANGE:
		tetromino[0]->x = 1;    // the orange L piece
		tetromino[0]->y = 0;    // 
		tetromino[1]->x = 1;    // 0 1 0
		tetromino[1]->y = 1;    // 0 1 0
		tetromino[2]->x = 1;    // 0 1 1
		tetromino[2]->y = 2;    // 
		tetromino[3]->x = 2;    //
		tetromino[3]->y = 2;    //
		break;
	case ColorsType::PINK:
		tetromino[0]->x = 1;	// the pink J piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 1;	// 0 1 0
		tetromino[1]->y = 1;	// 0 1 0
		tetromino[2]->x = 1;	// 1 1 0
		tetromino[2]->y = 2;	// 
		tetromino[3]->x = 0;	//
		tetromino[3]->y = 2;	//
		break;
	case ColorsType::PURPLE:
		tetromino[0]->x = 1;	// the purple T piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 1;	//
		tetromino[1]->y = 1;	// 0 1 0
		tetromino[2]->x = 0;	// 1 1 1
		tetromino[2]->y = 1;	// 0 0 0
		tetromino[3]->x = 2;	//
		tetromino[3]->y = 1;	//
		break;
	case ColorsType::RED:
		tetromino[0]->x = 0;	// the red Z piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 1;	//
		tetromino[1]->y = 1;	// 1 1 0
		tetromino[2]->x = 1;	// 0 1 1
		tetromino[2]->y = 0;	// 0 0 0
		tetromino[3]->x = 2;	//
		tetromino[3]->y = 1;	//
		break;
	case ColorsType::YELLOW:
		tetromino[0]->x = 0;	// the yellow O piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 1;	// 
		tetromino[1]->y = 0;	// 1 1 0 0
		tetromino[2]->x = 0;	// 1 1 0 0
		tetromino[2]->y = 1;	// 0 0 0 0
		tetromino[3]->x = 1;	// 0 0 0 0
		tetromino[3]->y = 1;	//
		break;
	}
	for (int i = 0; i < 4; i++)
	{
		tetromino[i]->y -= 4;
	}
	UpdateTetrominoPos();
}

void Piece::Shadow()
{
	for (int i = 0; i < PIECESIZE; i++)
	{
		tetromino[i]->SetTex(Shadowpiece);
	}
}

void Piece::UpdateTetrominoPos()
{
	int x, y;
	for (int i = 0; i < PIECESIZE; i++)
	{
		x = tetromino[i]->x;
		y = tetromino[i]->y;
		tetromino[i]->SetPosInd(y, x);
	}
	Xpos = GetMinXFromTet();
}

void Piece::MoveT(int dir)
{
	for (int i = 0; i < PIECESIZE; i++)
	{
		tetromino[i]->x += dir;
	}
	UpdateTetrominoPos();
}

void Piece::MoveTdown()
{
	for (int i = 0; i < PIECESIZE; i++)
	{
		tetromino[i]->y += 1;
	}
	UpdateTetrominoPos();
}

void Piece::MoveTup()
{
	for (int i = 0; i < PIECESIZE; i++)
	{
		tetromino[i]->y -= 1;
	}
	UpdateTetrominoPos();
}

void Piece::DrawT(sf::RenderWindow& window)
{
	for (int i = 0; i < PIECESIZE; i++)
	{
		window.draw(tetromino[i]->spr);
	}
}

void Piece::RotateTL()
{
	if (pivot != -1)
	{
		int y, x, tmpx, tmpy;
		for (int i = 0; i < PIECESIZE; i++)
		{
			if (i != pivot)
			{
				x = tetromino[i]->x;
				y = tetromino[i]->y;
				tmpx = tetromino[pivot]->x - x;
				tmpy = tetromino[pivot]->y - y;
				tetromino[i]->x += tmpx;
				tetromino[i]->x -= tmpy;
				tetromino[i]->y += tmpy;
				tetromino[i]->y += tmpx;
			}
		}
		if (curPieceColor == ColorsType::BLUE)
		{
			if (pivot == 2)
				pivot = 1;
			else
				pivot = 2;
		}
		UpdateTetrominoPos();
	}
}

void Piece::RotateTR()
{
	if (pivot != -1)
	{
		int y, x, tmpx, tmpy;
		for (int i = 0; i < PIECESIZE; i++)
		{
			if (i != pivot)
			{
				x = tetromino[i]->x;
				y = tetromino[i]->y;
				tmpx = tetromino[pivot]->x - x;
				tmpy = tetromino[pivot]->y - y;
				tetromino[i]->x += tmpx;
				tetromino[i]->x += tmpy;
				tetromino[i]->y += tmpy;
				tetromino[i]->y -= tmpx;
			}
		}
		if (curPieceColor == ColorsType::BLUE)
		{
			if (pivot == 2)
				pivot = 1;
			else
				pivot = 2;
		}
		UpdateTetrominoPos();
	}
}

////////////////



