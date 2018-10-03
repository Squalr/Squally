#include "StateRoundEnd.h"

StateRoundEnd* StateRoundEnd::create()
{
	StateRoundEnd* instance = new StateRoundEnd();

	instance->autorelease();

	return instance;
}

StateRoundEnd::StateRoundEnd() : StateBase(GameState::StateType::RoundEnd)
{
}

StateRoundEnd::~StateRoundEnd()
{
}

void StateRoundEnd::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateRoundEnd::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	if (gameState->playerLosses >= 2 || gameState->enemyLosses >= 2)
	{
		GameState::updateState(gameState, GameState::StateType::GameEnd);
	}
	else
	{
		GameState::updateState(gameState, GameState::StateType::RoundStart);
	}
}

void StateRoundEnd::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateRoundEnd::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
