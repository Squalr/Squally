#include "StateAIDecidePass.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Hexus/CardRow.h"

using namespace cocos2d;

StateAIDecidePass* StateAIDecidePass::create()
{
	StateAIDecidePass* instance = new StateAIDecidePass();

	instance->autorelease();

	return instance;
}

StateAIDecidePass::StateAIDecidePass() : super(GameState::StateType::AIDecidePass)
{
}

StateAIDecidePass::~StateAIDecidePass()
{
}

void StateAIDecidePass::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateAIDecidePass::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	CardData* strongestCardInDeck = gameState->opponentData->getStrongestCard();
	int strongestAttack = strongestCardInDeck == nullptr ? 1 : int(strongestCardInDeck->attack);
	int passIfDiffAboveOrEqual = int(float(strongestAttack) * 2.5f);
	CallFunc* stateTransition = nullptr;

	if (gameState->enemyHand->rowCards.size() == 0)
	{
		stateTransition = CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::Pass);
		});
	}
	// If the player passes and we're ahead we won, so pass
	else if (gameState->playerPassed && gameState->isEnemyWinningRound())
	{
		stateTransition = CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::Pass);
		});
	}
	// Pass or last stand if the player is significantly ahead, but not if the opponent can lose the game from this round
	else if (gameState->enemyLosses < 1 && (gameState->getPlayerTotal() >= gameState->getEnemyTotal() + passIfDiffAboveOrEqual))
	{
		stateTransition = CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::Pass);
		});
	}
	// Pass or last stand if the opponent is significantly ahead, but not if the opponent can lose the game from this round
	else if (gameState->enemyLosses < 1 && (gameState->getEnemyTotal() >= gameState->getPlayerTotal() + passIfDiffAboveOrEqual))
	{
		stateTransition = CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::Pass);
		});
	}
	else
	{
		stateTransition = CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::AIDecideCard);
		});
	}

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		stateTransition,
		nullptr
	));
}

void StateAIDecidePass::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateAIDecidePass::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
