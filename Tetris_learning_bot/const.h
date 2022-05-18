#pragma once
#include "SFML/Graphics.hpp"
#include "AssetManager.h"
#include <list>
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

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

#define Shadowpiece	"assets/shadow.png"
#define NOpiece		"assets/grey.png"
#define Ipiece		"assets/blue.png"
#define Spiece		"assets/green.png"
#define Lpiece		"assets/orange.png"
#define Jpiece		"assets/pink.png"
#define Tpiece		"assets/purple.png"
#define Zpiece		"assets/red.png"
#define Opiece		"assets/yellow.png"

#define SHADOWIpiece		"assets/shadow/blueshadow.png"
#define SHADOWSpiece		"assets/shadow/greenshadow.png"
#define SHADOWLpiece		"assets/shadow/orangeshadow.png"
#define SHADOWJpiece		"assets/shadow/pinkshadow.png"
#define SHADOWTpiece		"assets/shadow/purpleshadow.png"
#define SHADOWZpiece		"assets/shadow/redshadow.png"
#define SHADOWOpiece		"assets/shadow/yellowshadow.png"
