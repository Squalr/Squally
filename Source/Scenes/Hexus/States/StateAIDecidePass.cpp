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

	const int passIfDiffAbove = 30; // Give up if player is too far ahead
	const int cardsToSaveForLastRound = 4;

	CallFunc* stateTransition = nullptr;

	if (gameState->enemyHand->rowCards->size() == 0)
	{
		stateTransition = CallFunc::create([=]()
		{
			SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
			GameState::updateState(gameState, GameState::StateType::Pass);
		});
	}
	else if (gameState->enemyLosses < 1 && gameState->getPlayerTotal() > gameState->getEnemyTotal() + passIfDiffAbove)
	{
		stateTransition = CallFunc::create([=]()
		{
			SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
			GameState::updateState(gameState, GameState::StateType::Pass);
		});
	}
	// If it's not the last round we better save some cards
	else if (gameState->enemyLosses < 1 && gameState->enemyHand->rowCards->size() <= cardsToSaveForLastRound)
	{
		stateTransition = CallFunc::create([=]()
		{
			SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
			GameState::updateState(gameState, GameState::StateType::Pass);
		});
	}
	// If the player passes and we're ahead we won, so pass
	else if (gameState->playerPassed && gameState->enemyIsWinning())
	{
		stateTransition = CallFunc::create([=]()
		{
			SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
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
	StateBase::onStateReload(gameState);
}

void StateAIDecidePass::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
