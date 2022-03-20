#pragma once
#include "const.h"
class Cell
{
public:
	int x;
	int y;
	bool val;
	sf::Sprite spr;
	Cell();
	void SetTex(std::string& filename);
};

