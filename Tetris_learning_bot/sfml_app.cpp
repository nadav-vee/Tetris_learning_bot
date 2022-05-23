#include <SFML/Graphics.hpp>
#include "UserGame.h"
#include "AIGame.h"

int main()
{
	srand(unsigned int(time(NULL)));

	AssetManager manager;

	sf::ContextSettings windowSettings;
	windowSettings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(W, H), "TETRIS AI", sf::Style::Default/*, windowSettings*/);

	UserGame* u = new UserGame();
	AIGame* AIG = new AIGame();
	sf::Vector2i mousePos;

	sf::Sprite userGameSpr(AssetManager::GetTexture(USERGAMESPRITE));
	userGameSpr.setPosition(BUFF / 2, BUFF);
	userGameSpr.setScale((W - BUFF) / userGameSpr.getGlobalBounds().width,
		(H / 2 - BUFF) / userGameSpr.getGlobalBounds().height);
	sf::Sprite aiGameSpr(AssetManager::GetTexture(AIGAMESPRITE));
	aiGameSpr.setPosition(BUFF / 2, (H / 2 + BUFF / 2));
	aiGameSpr.setScale((W - BUFF) / aiGameSpr.getGlobalBounds().width, (H / 2 - BUFF) / aiGameSpr.getGlobalBounds().height);
	sf::Sprite tetrisSpr(AssetManager::GetTexture(TETRISSPR));
	tetrisSpr.setPosition(BUFF * 4, 0);
	tetrisSpr.setScale((W - (8 * BUFF)) / tetrisSpr.getGlobalBounds().width, BUFF / tetrisSpr.getGlobalBounds().height);
	bool hoverUserToggle = false, hoverAIToggle = false;
	sf::RectangleShape hoverUserRect;
	hoverUserRect.setPosition(userGameSpr.getPosition());
	hoverUserRect.setSize(sf::Vector2f(userGameSpr.getGlobalBounds().width, userGameSpr.getGlobalBounds().height));
	hoverUserRect.setFillColor(sf::Color::Transparent);
	hoverUserRect.setOutlineColor(sf::Color::White);
	hoverUserRect.setOutlineThickness(10);
	sf::RectangleShape hoverAIRect;
	hoverAIRect.setPosition(aiGameSpr.getPosition());
	hoverAIRect.setSize(sf::Vector2f(aiGameSpr.getGlobalBounds().width, aiGameSpr.getGlobalBounds().height));
	hoverAIRect.setFillColor(sf::Color::Transparent);
	hoverAIRect.setOutlineColor(sf::Color::White);
	hoverAIRect.setOutlineThickness(10);

	sf::Image icon;
	icon.loadFromFile(TETRISSPR);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	window.setFramerateLimit(60);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		mousePos = sf::Mouse::getPosition(window);

		// AIG->Start(window);
		
		if (userGameSpr.getGlobalBounds().contains(sf::Vector2f(mousePos)))
		{
			hoverUserToggle = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				u->Start(window);
			}
		}
		else
			hoverUserToggle = false;

		if (aiGameSpr.getGlobalBounds().contains(sf::Vector2f(mousePos)))
		{
			hoverAIToggle = true;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				AIG->Start(window);
			}
		}
		else
			hoverAIToggle = false;

		window.clear();

		window.draw(userGameSpr);
		window.draw(tetrisSpr);
		window.draw(aiGameSpr);
		if (hoverAIToggle)
			window.draw(hoverAIRect);
		if (hoverUserToggle)
			window.draw(hoverUserRect);

		window.display();
	}

	return 0;
}