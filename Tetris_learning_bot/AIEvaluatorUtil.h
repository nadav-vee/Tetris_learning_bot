#pragma once

#include "AICommon.h"
#include "const.h"
#include "Stack.h"
#include "AIEvaluatorComponent.h"
class AIEvaluatorUtil
{
public:
	AIEvaluatorUtil();
	~AIEvaluatorUtil();

	static void FindBestMove(AIEvaluatorComponent* comp);
private:
	static DesiredMoveSet __FindBestMove(Stack* tetrisBoard, class AIEvaluatorComponent* ownerComp, int lookaheads, bool holdPiece);
};

