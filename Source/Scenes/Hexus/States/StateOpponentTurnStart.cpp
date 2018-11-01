#include "StateOpponentTurnStart.h"

StateOpponentTurnStart* StateOpponentTurnStart::create()
{
	StateOpponentTurnStart* instance = new StateOpponentTurnStart();

	instance->autorelease();

	return instance;
}

StateOpponentTurnStart::StateOpponentTurnStart() : StateBase(GameState::StateType::OpponentTurnStart)
{
}

StateOpponentTurnStart::~StateOpponentTurnStart()
{
}

void StateOpponentTurnStart::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateOpponentTurnStart::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	gameState->remainingCards = Config::playableCardsPerTurn;

	this->runAction(Sequence::create(
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::Draw);
		}),
		nullptr
	));
}

void StateOpponentTurnStart::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateOpponentTurnStart::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
