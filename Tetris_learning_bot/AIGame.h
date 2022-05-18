#pragma once
#include "AI.h"

class AIGame
{
public:
	AIGame();
	void Start();
	void Update();
	void Draw();
	
private:
	AI *ai;
};

