#pragma once
#include "Stack.h"

class AI
{
public:
	AI();
	
	Stack* GetState();
	void Calc_Best_Outcome();
	void Update();
	void Start();
	void Learn();
private:
	Stack* CurState;
};

