#include "Cell.h"

Cell::Cell() : colorFileName(NOpiece)
{
	x = 0;
	y = 0;
	val = false;
	spr.setTexture(AssetManager::GetTexture(NOpiece));
	spr.setScale(SCALE, SCALE);
}

void Cell::SetTex(std::string const& filename)
{
	if (val == true)
	{
		spr.setTexture(AssetManager::GetTexture(filename));
		colorFileName = filename;
	}
}

void Cell::SetPosInd(int i, int j) // height, width
{
	spr.setPosition(j * SIZE * SCALE + PLH, i * SIZE * SCALE + PLH);
}

