#include "Cell.h"

Cell::Cell()
{
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
