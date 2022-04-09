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
#define PLH				(SIZE*SCALE*PIECELIST*PIECESIZE)
#define W				(BW+BUFF+PLW)
#define H				(BH)
#define LINECLRSCORE	100
#define TETRISSCORE		800
#define BCKTOBCKSCORE	1200
#define STARTINGXVAL	4

#define FONT		"font.ttf"

#define IDKpiece	"whiteish.png"
#define NOpiece		"grey.png"
#define Ipiece		"blue.png"
#define Spiece		"green.png"
#define Lpiece		"orange.png"
#define Jpiece		"pink.png"
#define Tpiece		"purple.png"
#define Zpiece		"red.png"
#define Opiece		"yellow.png"
