#pragma once
#include "Piece.h"

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



class Stack
{
public:
    Stack();
    ~Stack();
    bool Update();
    void Draw(sf::RenderWindow& window);
    void CopyPeiceToStack();
    void GameLogic(bool right, bool left, bool RotR, bool RotL);
    bool BlocksColl();
    bool WallsColl();
    bool BottomColl();
    bool StackColl();
    int DeleteLine(int index); // returns score



    void TemporaryChangepieceMethode();
    void GeneratepiecesQueue();
    Piece* curpiece;
    int Score;

private:
    Cell* board[STACKH][STACKW];
    std::queue<Piece*> Qpieces;
};

