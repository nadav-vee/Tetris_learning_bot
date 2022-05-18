#include "AIEvaluatorComponent.h"
#include "AIHeuristic.h"

AIEvaluatorComponent::AIEvaluatorComponent(Stack* owner)
{
	this->owner = owner;
	m_timeSinceLastUpdate = 0.0f + rand() / (float)RAND_MAX;
}


AIEvaluatorComponent::~AIEvaluatorComponent()
{
}
