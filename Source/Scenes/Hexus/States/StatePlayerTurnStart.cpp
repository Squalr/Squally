#include "StatePlayerTurnStart.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Hexus/Config.h"

using namespace cocos2d;

StatePlayerTurnStart* StatePlayerTurnStart::create()
{
	StatePlayerTurnStart* instance = new StatePlayerTurnStart();

	instance->autorelease();

	return instance;
}

StatePlayerTurnStart::StatePlayerTurnStart() : super(GameState::StateType::PlayerTurnStart)
{
}

StatePlayerTurnStart::~StatePlayerTurnStart()
{
}

void StatePlayerTurnStart::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);

	gameState->playerCardsDrawnNextRound += Config::cardBonusPerTurn;
}

void StatePlayerTurnStart::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	gameState->playableCardsThisTurn = Config::playableCardsPerTurn;
}

void StatePlayerTurnStart::onAfterStateEnter(GameState* gameState)
{
	GameState::updateState(gameState, GameState::StateType::Neutral);
}

void StatePlayerTurnStart::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StatePlayerTurnStart::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
