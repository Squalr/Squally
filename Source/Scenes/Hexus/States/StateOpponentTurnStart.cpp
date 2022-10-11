#include "StateOpponentTurnStart.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Hexus/HexusConfig.h"

using namespace cocos2d;

StateOpponentTurnStart* StateOpponentTurnStart::create()
{
	StateOpponentTurnStart* instance = new StateOpponentTurnStart();

	instance->autorelease();

	return instance;
}

StateOpponentTurnStart::StateOpponentTurnStart() : super(GameState::StateType::OpponentTurnStart)
{
}

StateOpponentTurnStart::~StateOpponentTurnStart()
{
}

void StateOpponentTurnStart::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);

	gameState->enemyCardsDrawnNextRound += HexusConfig::cardBonusPerTurn;
}

void StateOpponentTurnStart::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	gameState->playableCardsThisTurn = HexusConfig::playableCardsPerTurn;

	this->runAction(Sequence::create(
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::AIDecidePass);
		}),
		nullptr
	));
}

void StateOpponentTurnStart::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateOpponentTurnStart::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
