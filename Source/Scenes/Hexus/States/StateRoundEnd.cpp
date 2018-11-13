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

	if (gameState->playerLosses >= 2)
	{
		nextState = GameState::StateType::GameEnd;
		SoundManager::playSoundResource(Resources::Sounds_Hexus_Defeat);
	}
	else if (gameState->enemyLosses >= 2)
	{
		nextState = GameState::StateType::GameEnd;
		SoundManager::playSoundResource(Resources::Sounds_Hexus_Victory);
	}

	const float fadeSpeed = 0.5f;

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			std::vector<CardRow*> rows = gameState->getAllRows();

			for (auto it = rows.begin(); it != rows.end(); it++)
			{
				for (auto cardIt = (*it)->rowCards.begin(); cardIt != (*it)->rowCards.end(); cardIt++)
				{
					(*cardIt)->runAction(FadeTo::create(fadeSpeed, 0));
				}
			}
		}),
		DelayTime::create(Config::bannerDisplayDuration),
		CallFunc::create([=]()
		{
			gameState->removeFieldCards();
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
	StateBase::onStateReload(gameState);
}

void StateRoundEnd::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
