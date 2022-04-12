#pragma once
#include "SFML/Graphics.hpp"
#include "AssetManager.h"
#include <list>
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define PIECESIZE		4						// the amount of cells in a piece
#define SMALLPIECESIZE	3
#define STACKH			20
#define STACKW			10
#define SIZE			50
#define SCALE			0.7
#define BUFF			(SIZE*SCALE*2)
#define PIECELIST		5
#define BW				(SIZE*SCALE*STACKW)
#define BH				(SIZE*SCALE*STACKH)
#define PLW				(SIZE*SCALE*PIECESIZE)
#define PLH				(SIZE*SCALE*PIECESIZE)
#define W				(BW+PLW*3)
#define H				(BH + PLH + BUFF)
#define SCOREALLIGN		(BW + PLW + 10)
#define LINECLRSCORE	100
#define TETRISSCORE		800
#define BCKTOBCKSCORE	1200
#define STARTINGXVAL	4
#define NEXTPXVAL		11
#define HELDPYVAL		19

#define FONT		"font.ttf"

#define Shadowpiece	"shadow.png"
#define NOpiece		"grey.png"
#define Ipiece		"blue.png"
#define Spiece		"green.png"
#define Lpiece		"orange.png"
#define Jpiece		"pink.png"
#define Tpiece		"purple.png"
#define Zpiece		"red.png"
#define Opiece		"yellow.png"
