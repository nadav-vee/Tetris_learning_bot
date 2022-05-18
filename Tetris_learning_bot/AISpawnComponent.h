#pragma once

#include "Component.h"

struct GameInfo;

class AISpawnComponent
{
public:
	struct SpawnInfo
	{		
		float updateFrequency;
		sf::Vector2f aiHeursticRange;
		sf::Vector2f spawnPos;
		sf::Vector2f spawnScale;

		SpawnInfo()
			: updateFrequency(00)
			, spawnPos(0,0)
			, spawnScale(1,1)
			, aiHeursticRange(1.0f,1.0f)
		{

		}
	};	

	AISpawnComponent(Stack* tetris);
	~AISpawnComponent();
	void InitAI(float flUpdateFrequency, sf::Vector2f aiHeuristicRange);
	void Quit();

	sf::Vector2f m_aiSpawnPos;
	float m_flScale;
	float m_flXOffset;
	float m_flYOffset;
};

