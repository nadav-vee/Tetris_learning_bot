//#pragma once
//#include "AICommon.h"
//#include "Stack.h"
//
//
//
//class AIHeuristic;
//class AIDebugHeuristic;
//class AIEvaluatorComponent
//{
//public:
//	AIEvaluatorComponent(Stack* owner);
//	virtual ~AIEvaluatorComponent();
//
//	bool CanFindMove() { return m_timeSinceLastUpdate > AI_UPDATE_RATE_SECONDS; }
//	DesiredMoveSet GetBestMove() { return m_bestMoves[0]; }			
//	bool m_initialized;
//	float m_timeSinceLastUpdate;
//	sf::Vector2f m_aiHeuristicRange;
//	std::vector<AIHeuristic*> m_heuristics;
//	std::vector<AIDebugHeuristic> m_debugHeuristics;
//	DesiredMoveSet m_bestMoves[NUM_LOOKAHEAD];
//	Stack* owner;
//};
//
