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

enum buff{BUFFTOPIECE,PIECETOBUFF};

class Stack
{
public:
    Stack();
    ~Stack();
    bool Update();
    void Draw(sf::RenderWindow& window);
    int CopyPeiceToStack();
    void GameLogic(bool right, bool left, bool RotR, bool RotL, bool tochange, bool dropp, bool fasterdown);
    bool BlocksColl();
    bool WallsColl();
    bool BottomColl();
    bool StackColl();
    void CheckScore(int index); // returns scor



    void TemporaryChangepieceMethode();
    void GeneratepiecesQueue();
    void CopyPieceFunc(enum buff buf);
    Piece* curpiece;
    Piece* curpieceBuffer;
    int Score = 0;
    bool Combo = false;

private:
    bool CheckToDel(int index);
    void DeleteLine(int index);
    bool CheckTetris(int index); // returns score
    Cell* board[STACKH][STACKW];
    std::queue<Piece*> Qpieces;
};

// idea : 
// make a piece buffer. that way you can revert 
// moves in a smart way that won't cause trouble
// with the rest of the code

// idea: ( and game plan)
// in order to make code generic and built for 
// an ai to play it as well i'd have to seperate
// userGame to a Game class and a UserGame class.
// i'll also have to add a function that will check
// the user input. (maybe through reference)
// for the ai to be generic and seperate from the code
// i'll have to be able to get the current state of the
// game, calculate the best set of moves in the ai
// and evetually send them.
//      - get the current state
//      - calculate set of moves
//      - spread them