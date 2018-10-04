#include "StateAIDecideCardReplace.h"

StateAIDecideCardReplace* StateAIDecideCardReplace::create()
{
	StateAIDecideCardReplace* instance = new StateAIDecideCardReplace();

	instance->autorelease();

	return instance;
}

StateAIDecideCardReplace::StateAIDecideCardReplace() : StateBase(GameState::StateType::AIDecideCardReplace)
{
}

StateAIDecideCardReplace::~StateAIDecideCardReplace()
{
}

void StateAIDecideCardReplace::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);

	if (gameState->roundNumber == 0)
	{
		gameState->cardReplaceCount = std::min(3, gameState->enemyDeck->getCardCount());
	}
	else
	{
		gameState->cardReplaceCount = std::min(1, gameState->enemyDeck->getCardCount());
	}
}

void StateAIDecideCardReplace::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	this->runAction(Sequence::create(
		DelayTime::create(Config::bannerDisplayDuration),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::CardReplace);
		}),
		nullptr
	));
}

void StateAIDecideCardReplace::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateAIDecideCardReplace::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
