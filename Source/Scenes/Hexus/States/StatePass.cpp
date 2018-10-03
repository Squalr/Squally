#include "StatePass.h"

StatePass* StatePass::create()
{
	StatePass* instance = new StatePass();

	instance->autorelease();

	return instance;
}

StatePass::StatePass() : StateBase(GameState::StateType::Pass)
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

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::TurnEnd);
		}),
		nullptr
	));
}

void StatePass::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StatePass::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
