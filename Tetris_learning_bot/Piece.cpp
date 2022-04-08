#include "Piece.h"


Piece::Piece(enum ColorsType piecetype)
{

	for (int i = 0; i < PIECESIZE; i++)
	{
		tetromino[i] = new Cell();
		tetromino[i]->val = true;
	}
	pivot = 1;

	curPieceColor = piecetype;
	std::string filet;
	switch (piecetype)
	{
	case ColorsType::WHITEISH:
		break;
	case ColorsType::GREY:
		break;
	case ColorsType::BLUE:
		filet = Ipiece;
		pivot = 2;
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
		tetromino[0]->SetTex(filet);
		tetromino[1]->SetTex(filet);
		tetromino[2]->SetTex(filet);
		tetromino[3]->SetTex(filet);
		tetromino[0]->x = 1;	// the green S piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 2;	// 
		tetromino[1]->y = 0;	// 0 1 1
		tetromino[2]->x = 0;	// 1 1 0
		tetromino[2]->y = 1;	// 0 0 0
		tetromino[3]->x = 1;	//
		tetromino[3]->y = 1;	//
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
		tetromino[1]->x = 0;	//
		tetromino[1]->y = 1;	// 0 1 0
		tetromino[2]->x = 1;	// 1 1 1
		tetromino[2]->y = 1;	// 0 0 0
		tetromino[3]->x = 2;	//
		tetromino[3]->y = 1;	//
		break;
	case ColorsType::RED:
		filet = Zpiece;
		tetromino[0]->SetTex(filet);
		tetromino[1]->SetTex(filet);
		tetromino[2]->SetTex(filet);
		tetromino[3]->SetTex(filet);
		tetromino[0]->x = 0;	// the red Z piece
		tetromino[0]->y = 0;	// 
		tetromino[1]->x = 1;	//
		tetromino[1]->y = 0;	// 1 1 0
		tetromino[2]->x = 1;	// 0 1 1
		tetromino[2]->y = 1;	// 0 0 0
		tetromino[3]->x = 2;	//
		tetromino[3]->y = 1;	//
		break;
	case ColorsType::YELLOW:
		filet = Opiece;
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
	}                        //
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

void Piece::UpdateTetrominoPos()
{
	int x, y;
	for (int i = 0; i < PIECESIZE; i++)
	{
		x = tetromino[i]->x;
		y = tetromino[i]->y;
		tetromino[i]->spr.setPosition(x * SIZE * SCALE, y * SIZE * SCALE);
	}
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

void Piece::RotateTR()
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

////////////////



