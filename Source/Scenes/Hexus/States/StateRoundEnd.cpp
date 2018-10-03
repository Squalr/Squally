#include "StateRoundEnd.h"

StateRoundEnd* StateRoundEnd::create()
{
	StateRoundEnd* instance = new StateRoundEnd();

	instance->autorelease();

	return instance;
}

StateRoundEnd::StateRoundEnd() : StateBase(GameState::StateType::RoundEnd)
{
}

StateRoundEnd::~StateRoundEnd()
{
}

void StateRoundEnd::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateRoundEnd::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	gameState->endRound();

	if (gameState->playerLosses >= 2)
	{
		SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_card_downgrade);
	}
	else if (gameState->enemyLosses >= 2)
	{
		SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_card_upgrade);
	}
	else
	{
		// Player cannot enter the last round with zero cards
		if (gameState->playerHand->getCardCount() == 0)
		{
			gameState->playerLosses++;
			SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_card_downgrade);
		}
		else
		{
			this->runAction(Sequence::create(
				DelayTime::create(0.5f),
				CallFunc::create([=]()
				{
					GameState::updateState(gameState, GameState::StateType::RoundStart);
				}),
				nullptr
			));
		}
	}

	if (gameState->playerLosses >= 2 || gameState->enemyLosses >= 2)
	{
		this->runAction(Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([=]()
			{
				GameState::updateState(gameState, GameState::StateType::GameEnd);
			}),
			nullptr
		));
	}
	else
	{
		this->runAction(Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([=]()
			{
				GameState::updateState(gameState, GameState::StateType::RoundStart);
			}),
			nullptr
		));
	}
}

void StateRoundEnd::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateRoundEnd::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
