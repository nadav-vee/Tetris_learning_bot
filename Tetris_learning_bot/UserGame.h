#pragma once
#include "Stack.h"

class UserGame
{
public:
	UserGame();
	void Start(sf::RenderWindow& window);
private:
	sf::Text highscoreTX;
	sf::Text Score;
	sf::Text LosingMessage;
	sf::Font* font = new sf::Font();
	int HighScore = 0;
};

