#pragma once
#include "Cell.h"

/// ---------------------------------------------------------------------------------
/// a Stack conaining:
///	a matrix of bool (class?)
///		each cell needs to contain:
///		a bool value
///		a sprite value?
/// ======================
/// idea:
///		creating a cell type within the stack:
///		containing:
///			a bool value
///			a sprite
///			an update
///				gets:	cell value
///						original cell 
///				does: sets the sprite of the og cell to the new cell and resets
///				the og cell
///			a getter: returns the cell's sprite
///			a setter: gets a value and a sprite and sets these values
/// ======================
/// 
/// init logic:
///     creating the matricies (piece and stack)
///     generating a queue of pieces
///     
/// 
/// a draw function that uses a number of different textures (needs to get the window)
///		needs to get:
///		window
///		size and scale
/// 
/// size and scale (constants)
///
/// an update method
/// functions order:
///		reads input
///		does collision logic
///		sets new positions
///		draws maybe
///		does scoring and stack logic
///		calculates score
///		sets new positions if needed
///     generates new piece
///
/// a piece matrix of 4x4:
///		type needs to contain var:
///		a bool matrix
///		the texture within the sprite
///		the position within the entire stack
///		
/// ---------------------------------------------------------------------------------



enum ColorsType { WHITEISH, 
                   GREY, 
                  BLUE, 
                  GREEN, 
                  ORANGE, 
                  PINK, 
                  PURPLE, 
                  RED, 
                  YELLOW};

class Piece
{
public:
    Piece(enum ColorsType piecetype);
    ~Piece();
    void SetpiecePos(sf::Vector2i ps);
    ColorsType getColorPiece();
    sf::Vector2i GetPiecePos();
    void Draw(sf::RenderWindow& window);
    void Rotate();
    void Move(int dir);
    void RotWithoutOrigin();
    void RotWithOrigin();
    sf::Vector2i StackIndPos;

private:
    //sf::Vector2i Origin;
    Cell* piece[PIECESIZE][PIECESIZE];
    Cell* smallpiece[SMALLPIECESIZE][SMALLPIECESIZE];
    void UpdatepiecePos();
    ColorsType curPieceColor;
};


class Stack
{
public:
    Stack();
    void Update();
    void Draw(sf::RenderWindow& window);
    void CopyPeiceToStack();

    bool StackColl();
    bool BottomColl();
    bool WallsColl();
    bool BlocksColl();
    int DeleteLine(int index); // returns score



    void TemporaryChangepieceMethode();
    void GeneratepiecesQueue();
    Piece* curpiece;

private:
    Cell* board[STACKH][STACKW];
    std::queue<Piece*> Qpieces;
};

