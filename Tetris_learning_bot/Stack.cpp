#include "Stack.h"


ColorsType rs()
{
	return (ColorsType)((rand() % 7) + 2);
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
	curpiece->SetpiecePos(sf::Vector2i(2, 3));

	GeneratepiecesQueue(); // generating the queue

}

void Stack::Update()
{
	curpiece->Rotate();
	sf::Vector2i curpos = curpiece->GetPiecePos();
	curpiece->SetpiecePos(sf::Vector2i(curpos.x, curpos.y + 1));
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
	curpiece->Draw(window);
	Qpieces.front()->Draw(window);
}



Piece* NewPiece(ColorsType rp)
{
	Piece* tmpP = new Piece(rp);
	tmpP->SetpiecePos(sf::Vector2i(8, 0));
	return tmpP;
}


void Stack::TemporaryChangepieceMethode()
{
	delete curpiece;
	Qpieces.push(NewPiece(rs())); // rs = random shape
	curpiece = Qpieces.front();
	Qpieces.pop();
	curpiece->SetpiecePos(sf::Vector2i(2, 3));
}

void Stack::GeneratepiecesQueue()
{
	for (int i = 0; i < PIECELIST; i++) // generating list
	{
		int Rpiece = ((rand() % 7) + 2);
		Qpieces.push(NewPiece((ColorsType)Rpiece));
	}
	//for (auto i = Qpieces.begin(); i != Qpieces.end(); i++) // setting positions for drawing
	//{
	//	for (int y = 0; y < pieceSIZE; y++)
	//	{
	//		for (int x = 0; x < pieceSIZE; x++)
	//		{

	//		}
	//	}
	//}

}

//////////////////////////////////////////////////////////////////////////// diff class

Piece::Piece(enum ColorsType piecetype)
{

	for (int i = 0; i < PIECESIZE; i++)
	{
		for (int j = 0; j < PIECESIZE; j++)
		{
			piece[i][j] = new Cell();
			piece[i][j]->spr.setScale(SCALE, SCALE);
			piece[i][j]->spr.setPosition(j * SIZE * SCALE, i * SIZE * SCALE);
		}
	} //piece init
	for (int i = 0; i < SMALLPIECESIZE; i++)
	{
		for (int j = 0; j < SMALLPIECESIZE; j++)
		{
			smallpiece[i][j] = new Cell();
			smallpiece[i][j]->spr.setScale(SCALE, SCALE);
			smallpiece[i][j]->spr.setPosition(j * SIZE * SCALE, i * SIZE * SCALE);
		}
	} //small piece init

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
		
		piece[0][1]->val = true;	// the blue I piece
		piece[0][1]->SetTex(filet); // 
		piece[1][1]->val = true;	// 0 1 0 0
		piece[1][1]->SetTex(filet); // 0 1 0 0
		piece[2][1]->val = true;	// 0 1 0 0
		piece[2][1]->SetTex(filet);	// 0 1 0 0
		piece[3][1]->val = true;	//
		piece[3][1]->SetTex(filet);	//
		break;
	case ColorsType::GREEN:
		filet = Spiece;
		
		smallpiece[0][1]->val = true;		// the green S piece
		smallpiece[0][1]->SetTex(filet);	// 
		smallpiece[0][2]->val = true;		// 
		smallpiece[0][2]->SetTex(filet);	// 0 1 1
		smallpiece[1][0]->val = true;		// 1 1 0
		smallpiece[1][0]->SetTex(filet);	// 0 0 0
		smallpiece[1][1]->val = true;		//
		smallpiece[1][1]->SetTex(filet);	//
		break;
	case ColorsType::ORANGE:
		filet = Lpiece;
		
		smallpiece[0][1]->val = true;		// the orange L piece
		smallpiece[0][1]->SetTex(filet);	// 
		smallpiece[1][1]->val = true;		// 0 1 0
		smallpiece[1][1]->SetTex(filet);	// 0 1 0
		smallpiece[2][1]->val = true;		// 0 1 1
		smallpiece[2][1]->SetTex(filet);	// 
		smallpiece[2][2]->val = true;		//
		smallpiece[2][2]->SetTex(filet);	//
		break;
	case ColorsType::PINK:
		filet = Jpiece;
		
		smallpiece[0][1]->val = true;		// the pink J piece
		smallpiece[0][1]->SetTex(filet);	// 
		smallpiece[1][1]->val = true;		// 0 1 0
		smallpiece[1][1]->SetTex(filet);	// 0 1 0
		smallpiece[2][0]->val = true;		// 1 1 0
		smallpiece[2][0]->SetTex(filet);	// 
		smallpiece[2][1]->val = true;		//
		smallpiece[2][1]->SetTex(filet);	//
		break;
	case ColorsType::PURPLE:
		filet = Tpiece;
		
		smallpiece[0][1]->val = true;		// the purple T piece
		smallpiece[0][1]->SetTex(filet);	// 
		smallpiece[1][0]->val = true;		//
		smallpiece[1][0]->SetTex(filet);	// 0 1 0
		smallpiece[1][1]->val = true;		// 1 1 1
		smallpiece[1][1]->SetTex(filet);	// 0 0 0
		smallpiece[1][2]->val = true;		//
		smallpiece[1][2]->SetTex(filet);	//
		break;
	case ColorsType::RED:
		filet = Zpiece;
		
		smallpiece[0][0]->val = true;		// the red Z piece
		smallpiece[0][0]->SetTex(filet);	// 
		smallpiece[0][1]->val = true;		//
		smallpiece[0][1]->SetTex(filet);	// 1 1 0
		smallpiece[1][1]->val = true;		// 0 1 1
		smallpiece[1][1]->SetTex(filet);	// 0 0 0
		smallpiece[1][2]->val = true;		//
		smallpiece[1][2]->SetTex(filet);	//
		break;
	case ColorsType::YELLOW:
		filet = Opiece;
		
		piece[1][1]->val = true;	// the yellow O piece
		piece[1][1]->SetTex(filet); // 
		piece[1][2]->val = true;	// 0 0 0 0
		piece[1][2]->SetTex(filet); // 0 1 1 0
		piece[2][1]->val = true;	// 0 1 1 0
		piece[2][1]->SetTex(filet);	// 0 0 0 0
		piece[2][2]->val = true;	//
		piece[2][2]->SetTex(filet);	//
		break;
	default:
		break;
	}                                                              //
}

Piece::~Piece()
{
	for (int i = 0; i < PIECESIZE; i++)
	{
		for (int j = 0; j < PIECESIZE; j++)
		{
			delete piece[i][j];
		}
	}
	for (int i = 0; i < SMALLPIECESIZE; i++)
	{
		for (int j = 0; j < SMALLPIECESIZE; j++)
		{
			delete smallpiece[i][j];
		}
	}
}

void Piece::SetpiecePos(sf::Vector2i ps)
{
	StackIndPos = ps;
	UpdatepiecePos();
}

ColorsType Piece::getColorPiece()
{
	return curPieceColor;
}

sf::Vector2i Piece::GetPiecePos()
{
	return StackIndPos;
}

void Piece::RotWithoutOrigin()
{
	Cell* tmp = new Cell();
	tmp = piece[0][0];
	piece[0][0] = piece[3][0];
	piece[3][0] = piece[3][3];
	piece[3][3] = piece[0][3];
	piece[0][3] = tmp;

	tmp = piece[0][1];
	piece[0][1] = piece[2][0];
	piece[2][0] = piece[3][2];
	piece[3][2] = piece[1][3];
	piece[0][0] = piece[3][0];
	piece[1][3] = tmp;

	tmp = piece[0][2];
	piece[0][2] = piece[1][0];
	piece[1][0] = piece[3][1];
	piece[3][1] = piece[2][3];
	piece[2][3] = tmp;

	tmp = piece[1][1];
	piece[1][1] = piece[2][1];
	piece[2][1] = piece[2][2];
	piece[2][2] = piece[1][2];
	piece[1][2] = tmp;
}

void Piece::RotWithOrigin()
{
	Cell* tmp = new Cell();
	tmp = smallpiece[0][0];
	smallpiece[0][0] = smallpiece[0][1];
	smallpiece[0][1] = smallpiece[0][2];
	smallpiece[0][2] = smallpiece[1][2];
	smallpiece[1][2] = smallpiece[2][2];
	smallpiece[2][2] = smallpiece[2][1];
	smallpiece[2][1] = smallpiece[2][0];
	smallpiece[2][0] = smallpiece[1][0];
	smallpiece[1][0] = tmp;
}

void Piece::Rotate()
{
	switch (curPieceColor)
	{
	case ColorsType::BLUE:
		RotWithoutOrigin();
		break;
	case ColorsType::YELLOW:
		break;
	case ColorsType::GREEN:
		RotWithOrigin();
		RotWithOrigin();
		break;
	case ColorsType::ORANGE:
		RotWithOrigin();
		RotWithOrigin();
		break;
	case ColorsType::PINK:
		RotWithOrigin();
		RotWithOrigin();
		break;
	case ColorsType::PURPLE:
		RotWithOrigin();
		RotWithOrigin();
		break;
	case ColorsType::RED:
		RotWithOrigin();
		RotWithOrigin();
		break;
	}
}
void Piece::Draw(sf::RenderWindow& window)
{
	UpdatepiecePos();
	if (curPieceColor == ColorsType::BLUE || curPieceColor == ColorsType::YELLOW)
	{
		for (int i = 0; i < PIECESIZE; i++)
		{
			for (int j = 0; j < PIECESIZE; j++)
			{
				window.draw(piece[i][j]->spr);
			}
		}
	}
	else
	{
		for (int i = 0; i < SMALLPIECESIZE; i++)
		{
			for (int j = 0; j < SMALLPIECESIZE; j++)
			{
				window.draw(smallpiece[i][j]->spr);
			}
		}
	}
}

void Piece::UpdatepiecePos()
{
	int x = StackIndPos.x;
	int y = StackIndPos.y;
	if (curPieceColor == ColorsType::BLUE || curPieceColor == ColorsType::YELLOW)
	{
		for (int i = 0; i < PIECESIZE; i++)
		{
			for (int j = 0; j < PIECESIZE; j++)
			{
				piece[i][j]->spr.setPosition((j + x) * SIZE * SCALE, (i + y) * SIZE * SCALE);
			}
		}
	}
	else 
	{
		for (int i = 0; i < SMALLPIECESIZE; i++)
		{
			for (int j = 0; j < SMALLPIECESIZE; j++)
			{
				smallpiece[i][j]->spr.setPosition((j + x) * SIZE * SCALE, (i + y) * SIZE * SCALE);
			}
		}
	}
}
