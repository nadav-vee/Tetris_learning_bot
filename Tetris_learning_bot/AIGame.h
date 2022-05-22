#pragma once
#include "AI.h"

class AIGame
{
public:
	AIGame();
	void Start();
	void Update(float dt);
	void Draw(sf::RenderWindow& window, float dt);
	
private:
	sf::RenderWindow* window;
	AI *ai;
};

