#include "StatePlayerTurnStart.h"

StatePlayerTurnStart* StatePlayerTurnStart::create()
{
	StatePlayerTurnStart* instance = new StatePlayerTurnStart();

	instance->autorelease();

	return instance;
}

StatePlayerTurnStart::StatePlayerTurnStart() : StateBase(GameState::StateType::PlayerTurnStart)
{
}

StatePlayerTurnStart::~StatePlayerTurnStart()
{
}

void StatePlayerTurnStart::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StatePlayerTurnStart::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	gameState->remainingCards = Config::playableCardsPerTurn;

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::Draw);
		}),
		nullptr
	));
}

void StatePlayerTurnStart::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StatePlayerTurnStart::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
