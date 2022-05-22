//#pragma once
//
//#include "AICommon.h"
//#include "Stack.h"
//
//#define AI_CONTROLLER_UPDATE_FREQUENCY (.00f)
//
//class AIControllerComponent
//{
//public:
//	AIControllerComponent(Stack* owner);
//	virtual ~AIControllerComponent();
//
//	void SetUpdateFrequency(float time) { m_updateFrequency = time; }
//	void SetCurrentMove(DesiredMoveSet& move)
//	{
//		if (move.id != m_currentMove.id)
//		{
//			m_currentMove = move;
//		}
//	}
//	bool NeedsNewMove()
//	{
//		return m_currentMove.used;
//	}
//
//	Stack* current;
//	DesiredMoveSet m_currentMove;
//	float m_timeUntilUpdate;
//	float m_updateFrequency;
//};
//
