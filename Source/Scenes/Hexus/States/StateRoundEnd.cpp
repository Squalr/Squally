#include "StateRoundEnd.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"

using namespace cocos2d;

StateRoundEnd* StateRoundEnd::create()
{
	StateRoundEnd* instance = new StateRoundEnd();

	instance->autorelease();

	return instance;
}

StateRoundEnd::StateRoundEnd() : super(GameState::StateType::RoundEnd)
{
}

StateRoundEnd::~StateRoundEnd()
{
}

void StateRoundEnd::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateRoundEnd::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	GameState::StateType nextState = GameState::StateType::RoundStart;

	if (gameState->isRoundTied())
	{
		gameState->enemyLosses++;
		gameState->playerLosses++;
	}
	else if (gameState->isPlayerWinningRound())
	{
		gameState->enemyLosses++;
	}
	else
	{
		gameState->playerLosses++;
	}

	if (gameState->playerLosses >= 2 || gameState->enemyLosses >= 2)
	{
		nextState = GameState::StateType::GameEnd;
	}

	const float fadeSpeed = 0.5f;

	this->runAction(Sequence::create(
		DelayTime::create(Config::bannerDisplayDuration),
		CallFunc::create([=]()
		{
			gameState->sendFieldCardsToGraveyard();
			gameState->roundNumber++;
		}),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, nextState);
		}),
		nullptr
	));
}

void StateRoundEnd::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateRoundEnd::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
