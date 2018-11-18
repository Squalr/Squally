#include "StateTutorial.h"

StateTutorial* StateTutorial::create()
{
	StateTutorial* instance = new StateTutorial();

	instance->autorelease();

	return instance;
}

StateTutorial::StateTutorial() : StateBase(GameState::StateType::Tutorial)
{
}

StateTutorial::~StateTutorial()
{
}

void StateTutorial::onAnyRequestStateChange(GameState* gameState)
{
	StateBase::onAnyRequestStateChange(gameState);
	
	// Hijack the neutral state and replace it with a tutorial state
	if (gameState->previousStateType != GameState::StateType::Tutorial && gameState->stateType == GameState::StateType::Neutral)
	{
		switch (gameState->tutorialMode)
		{
			case StateOverride::NoTutorial:
			{
				break;
			}
			default:
			{
				gameState->stateType = GameState::StateType::Tutorial;
				break;
			}
		}
	}
}

void StateTutorial::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateTutorial::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);
}

void StateTutorial::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateTutorial::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
