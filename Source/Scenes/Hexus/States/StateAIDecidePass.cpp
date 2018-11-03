#include "StateAIDecidePass.h"

StateAIDecidePass* StateAIDecidePass::create()
{
	StateAIDecidePass* instance = new StateAIDecidePass();

	instance->autorelease();

	return instance;
}

StateAIDecidePass::StateAIDecidePass() : StateBase(GameState::StateType::AIDecidePass)
{
}

StateAIDecidePass::~StateAIDecidePass()
{
}

void StateAIDecidePass::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateAIDecidePass::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	CardData* strongestCardInDeck = gameState->opponentData->getStrongestCard();
	int strongestAttack = (float)(strongestCardInDeck == nullptr ? 1 : strongestCardInDeck->attack);
	int passIfDiffAbove = (int)(strongestAttack * 2.5f);
	CallFunc* stateTransition = nullptr;

	GameState::StateType nextState = gameState->playerLastStanded ? GameState::StateType::Pass : GameState::StateType::LastStand;

	if (gameState->enemyHand->rowCards.size() == 0)
	{
		stateTransition = CallFunc::create([=]()
		{
			SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
			GameState::updateState(gameState, nextState);
		});
	}
	// If the player passes and we're ahead we won, so pass
	else if (gameState->playerLastStanded && gameState->isEnemyWinningRound())
	{
		stateTransition = CallFunc::create([=]()
		{
			SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
			GameState::updateState(gameState, nextState);
		});
	}
	// Pass or last stand if the player is significantly ahead, but not if the opponent can lose the game from this round
	else if (gameState->enemyLosses < 1 && gameState->getPlayerTotal() > gameState->getEnemyTotal() + passIfDiffAbove)
	{
		stateTransition = CallFunc::create([=]()
		{
			SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
			GameState::updateState(gameState, nextState);
		});
	}
	// Pass or last stand if the opponent is significantly ahead, but not if the opponent can lose the game from this round
	else if (gameState->enemyLosses < 1 && gameState->getEnemyTotal() > gameState->getPlayerTotal() + passIfDiffAbove)
	{
		stateTransition = CallFunc::create([=]()
		{
			SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
			GameState::updateState(gameState, nextState);
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
	StateBase::onStateReload(gameState);
}

void StateAIDecidePass::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
