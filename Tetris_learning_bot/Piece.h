#pragma once
#include "Cell.h"

enum ColorsType {
    SHADOW,
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
    void setColorPiece(ColorsType color);
    ////////////////
    void SetStartingPos();
    void SetNextPosition();
    void SetHeldPosition();
    void Shadow();
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
    void ResetPos();
    int pivot;
    //sf::Vector2i Origin;
    void UpdateTetrominoPos();
    ColorsType curPieceColor;
};