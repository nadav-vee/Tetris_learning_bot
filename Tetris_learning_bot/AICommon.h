#pragma once

#define DEFAULT_SCORE -99999
#define AI_CONTROLLER_UPDATE_FREQUENCY (.00f)

#define NUM_LOOKAHEAD (2)
#define AI_UPDATE_RATE_SECONDS (0.0f)


class DesiredMoveSet
{
public:
	DesiredMoveSet()
		: score(DEFAULT_SCORE)
		, id(-1)
		, numRotations(0)
		, col(0)
		, swapPiece(false)
		, used(false)
	{

	}


	float score;
	int id;
	int numRotations;
	int col;
	bool swapPiece;
	bool used;
};
