#pragma once
#include "Cell.h"

enum ColorsType {
    WHITEISH,
    GREY,
    BLUE,
    GREEN,
    ORANGE,
    PINK,
    PURPLE,
    RED,
    YELLOW
};

class Piece
{
public:
    Piece(enum ColorsType piecetype);
    ~Piece();
    ColorsType getColorPiece();
    ////////////////
    void MoveT(int dir);
    void MoveTdown();
    void MoveTup();
    void DrawT(sf::RenderWindow& window);
    void RotateTR();
    void RotateTL();
    ////////////////
    Cell* tetromino[PIECESIZE];

private:
    int pivot;
    //sf::Vector2i Origin;
    void UpdateTetrominoPos();
    ColorsType curPieceColor;
};