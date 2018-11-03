#include "StateRoundStart.h"

StateRoundStart* StateRoundStart::create()
{
	StateRoundStart* instance = new StateRoundStart();

	instance->autorelease();

	return instance;
}

StateRoundStart::StateRoundStart() : StateBase(GameState::StateType::RoundStart)
{
}

StateRoundStart::~StateRoundStart()
{
}

void StateRoundStart::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateRoundStart::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	gameState->turnNumber = 0;
	gameState->playerPassed = false;
	gameState->enemyPassed = false;

	// Clear last stand state
	gameState->penaltyCardsPlayed = 0;
	gameState->playerLastStanded = false;
	gameState->enemyLastStanded = false;

	this->runAction(Sequence::create(
		DelayTime::create(Config::bannerDisplayDuration),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::DrawInitialCards);
		}),
		nullptr
	));
}

void StateRoundStart::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateRoundStart::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
