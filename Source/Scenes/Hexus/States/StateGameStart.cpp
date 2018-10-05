#include "StateGameStart.h"

StateGameStart* StateGameStart::create()
{
	StateGameStart* instance = new StateGameStart();

	instance->autorelease();

	return instance;
}

StateGameStart::StateGameStart() : StateBase(GameState::StateType::GameStart)
{
}

StateGameStart::~StateGameStart()
{
}

void StateGameStart::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateGameStart::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	gameState->playerDeck->shuffle();
	gameState->enemyDeck->shuffle();

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::DrawInitialCards);
		}),
		nullptr
	));
}

void StateGameStart::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateGameStart::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
