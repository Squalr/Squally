#include "StatePass.h"

StatePass* StatePass::create()
{
	StatePass* instance = new StatePass();

	instance->autorelease();

	return instance;
}

StatePass::StatePass() : StateBase(GameState::StateType::TurnEnd)
{
}

StatePass::~StatePass()
{
}

void StatePass::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StatePass::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);
}

void StatePass::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StatePass::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
