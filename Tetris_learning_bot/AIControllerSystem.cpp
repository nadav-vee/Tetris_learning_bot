#include "AIControllerComponent.h"
#include "AIControllerSystem.h"
#include "Stack.h"

AIControllerSystem::AIControllerSystem(AIControllerComponent* comp) 
	: comp(comp)
{
}

void AIControllerSystem::Update(float dt)
{
	if (comp)
	{
		comp->m_timeUntilUpdate -= dt;

		while (comp->m_timeUntilUpdate <= 0.0f)
		{
			comp->m_timeUntilUpdate += comp->m_updateFrequency;
			if (!comp->m_currentMove.used && owner->curpiece)
			{
				if (comp->m_currentMove.swapPiece)
				{
					comp->m_currentMove.used = true;
					owner->SwitchPiece();
				}
				else
				{
					bool shouldDrop = true;
					if (owner->curpiece->m_originRotations < comp->m_currentMove.numRotations)
					{
						shouldDrop = false;
						owner->KeyRotate();
					}
					else if (comp->m_owner->m_currentPiece->m_originColIdx < comp->m_currentMove.col)
					{
						shouldDrop = false;
						comp->m_owner->KeyMoveRight();
					}
					else if (comp->m_owner->m_currentPiece->m_originColIdx > comp->m_currentMove.col)
					{
						shouldDrop = false;
						comp->m_owner->KeyMoveLeft();
					}

					if (shouldDrop)
					{
						comp->m_currentMove.used = true;
						comp->m_owner->KeyDrop();
					}
				}
			}
		}
	}
}