#include "StateAIDecidePass.h"

StateAIDecidePass* StateAIDecidePass::create()
{
	StateAIDecidePass* instance = new StateAIDecidePass();

	instance->autorelease();

	return instance;
}

StateAIDecidePass::StateAIDecidePass() : StateBase(GameState::StateType::AIDecidePass)
{
}

StateAIDecidePass::~StateAIDecidePass()
{
}

void StateAIDecidePass::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateAIDecidePass::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);
}

void StateAIDecidePass::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateAIDecidePass::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
