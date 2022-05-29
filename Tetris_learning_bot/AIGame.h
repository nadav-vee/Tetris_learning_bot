#pragma once
#include "AI.h"

class AIGame
{
public:
	AIGame();
	void Start(sf::RenderWindow& window);
	void Update(float dt, bool* res);
	void Draw(sf::RenderWindow& window, float dt);
	
private:
	sf::RenderWindow* window;
	AI *ai;
	sf::Text highscoreTX;
	sf::Text Score;
	sf::Text LosingMessage;
	sf::Font* font = new sf::Font();
	int HighScore = 0;
	bool toggleDebug = false;
};

