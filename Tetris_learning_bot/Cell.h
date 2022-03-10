#pragma once
#include "const.h"
class Cell
{
public:
	Cell();
	void SetTex(std::string& filename);
	bool val;
	sf::Sprite spr;
};

