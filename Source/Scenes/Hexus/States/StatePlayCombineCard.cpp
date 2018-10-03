#include "StatePlayCombineCard.h"

StatePlayCombineCard* StatePlayCombineCard::create()
{
	StatePlayCombineCard* instance = new StatePlayCombineCard();

	instance->autorelease();

	return instance;
}

StatePlayCombineCard::StatePlayCombineCard() : StateBase(GameState::StateType::PlayCombineCard)
{
}

StatePlayCombineCard::~StatePlayCombineCard()
{
}

void StatePlayCombineCard::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StatePlayCombineCard::onStateEnter(GameState* gameState)
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

void StatePlayCombineCard::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StatePlayCombineCard::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
