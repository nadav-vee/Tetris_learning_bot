#include "Cell.h"

Cell::Cell()
{
	x = 0;
	y = 0;
	val = false;
	spr.setTexture(AssetManager::GetTexture(NOpiece));
}

void Cell::SetTex(std::string& filename)
{
	if (val == true)
	{
		spr.setTexture(AssetManager::GetTexture(filename));
	}
}
