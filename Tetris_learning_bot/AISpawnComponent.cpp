//#include "const.h"
//#include "AISpawnComponent.h"
//#include "Stack.h"
//
//AISpawnComponent::AISpawnComponent(Stack * tetris)
//	:  m_aiSpawnPos(0,0)
//{
//	m_aiSpawnPos.x = BW;
//	m_aiSpawnPos.y = 0;
//	
//	m_flScale = 0.5f;
//	m_flXOffset = BW * m_flScale;
//	m_flYOffset = BH * m_flScale + 50;
//}
//
//AISpawnComponent::~AISpawnComponent()
//{
//}
//void AISpawnComponent::Quit()
//{
//
//}
//
//void AISpawnComponent::InitAI(float flUpdateFrequency, sf::Vector2f flAIHeuristicRange)
//{	
//	SpawnInfo newAI;
//
//	newAI.spawnPos = m_aiSpawnPos;
//	newAI.spawnScale = sf::Vector2f(m_flScale, m_flScale);
//	newAI.aiHeursticRange = flAIHeuristicRange;
//	newAI.updateFrequency = flUpdateFrequency;	
//
//	m_aiSpawnPos.x += m_flXOffset;
//
//	if (m_aiSpawnPos.x >= W - m_flXOffset)
//	{
//		m_aiSpawnPos.x = BW;
//		m_aiSpawnPos.y += m_flYOffset;
//	}
//}
