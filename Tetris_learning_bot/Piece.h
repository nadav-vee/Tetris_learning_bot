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
    void SetPosition(int x, int y); // Function assumes piece in base position (0,0)
    void SetStartingPos();
    void SetNextPosition();
    void SetHeldPosition();
    void Shadow();
    ////////////////
    void MoveX(int dir);
    void MoveY(int dir);
    void MoveTdown();
    void MoveTup();
    void DrawT(sf::RenderWindow& window);
    void RotateTR();
    void RotateTL();
    ////////////////
    Cell* tetromino[PIECESIZE];
    int maxRotations;
    int Xpos;
    int Ypos;
    int pivot;
    void ResetPos();
    void UpdatePos();

private:
    //sf::Vector2i Origin;
    int GetMinYFromTet();
    int GetMinXFromTet();
    ColorsType curPieceColor;
};