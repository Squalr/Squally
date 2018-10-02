#include "StateRoundEnd.h"

StateRoundEnd* StateRoundEnd::create()
{
	StateRoundEnd* instance = new StateRoundEnd();

	instance->autorelease();

	return instance;
}

StateRoundEnd::StateRoundEnd() : StateBase(GameState::StateType::TurnEnd)
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
}

void StateRoundEnd::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateRoundEnd::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
