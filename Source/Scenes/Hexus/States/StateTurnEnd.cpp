#include "StateTurnEnd.h"

StateTurnEnd* StateTurnEnd::create()
{
	StateTurnEnd* instance = new StateTurnEnd();

	instance->autorelease();

	return instance;
}

StateTurnEnd::StateTurnEnd() : StateBase(GameState::StateType::TurnEnd)
{
}

StateTurnEnd::~StateTurnEnd()
{
}

void StateTurnEnd::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);

	gameState->turnNumber++;
}

void StateTurnEnd::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	gameState->clearInteraction();

	float endTurnDelay = Config::endTurnDelay;
	gameState->isRepeatingSameTurn = false;
	gameState->selectedRow = nullptr;
	gameState->selectedSourceCard = nullptr;
	gameState->selectedDestinationCard = nullptr;

	// If both players passed than we end the round
	if (gameState->playerPassed && gameState->enemyPassed)
	{
		CallFunc* changeState = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::RoundEnd);
		});

		this->runAction(Sequence::create(
			DelayTime::create(endTurnDelay),
			DelayTime::create(Config::betweenTurnDelay),
			changeState,
			nullptr
		));
		return;
	}

	// If the player passed it is the enemies turn
	if (gameState->playerPassed)
	{
		if (gameState->turn == GameState::Turn::Enemy)
		{
			gameState->isRepeatingSameTurn = true;
		}

		endTurnDelay = Config::enemyEndTurnDelay;
		gameState->turn = GameState::Turn::Enemy;
		CallFunc* changeState = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::OpponentTurnStart);
		});

		this->runAction(Sequence::create(
			DelayTime::create(endTurnDelay),
			DelayTime::create(Config::betweenTurnDelay),
			changeState,
			nullptr
		));
		return;
	}

	// If the enemy passed it is the players turn
	if (gameState->enemyPassed)
	{
		if (gameState->turn == GameState::Turn::Player)
		{
			gameState->isRepeatingSameTurn = true;
		}

		gameState->turn = GameState::Turn::Player;
		CallFunc* changeState = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::PlayerTurnStart);
		});

		this->runAction(Sequence::create(
			DelayTime::create(endTurnDelay),
			DelayTime::create(Config::betweenTurnDelay),
			changeState,
			nullptr
		));
		return;
	}

	// If no one has activated last stand we alternate turns
	switch (gameState->turn)
	{
		case GameState::Turn::Enemy:
		{
			endTurnDelay = Config::enemyEndTurnDelay;
			gameState->turn = GameState::Turn::Player;
			CallFunc* changeState = CallFunc::create([gameState]
			{
				GameState::updateState(gameState, GameState::StateType::PlayerTurnStart);
			});

			this->runAction(Sequence::create(
				DelayTime::create(endTurnDelay),
				DelayTime::create(Config::betweenTurnDelay),
				changeState,
				nullptr
			));
			break;
		}
		case GameState::Turn::Player:
		{
			gameState->turn = GameState::Turn::Enemy;

			CallFunc* changeState = CallFunc::create([gameState]
			{
				GameState::updateState(gameState, GameState::StateType::OpponentTurnStart);
			});

			this->runAction(Sequence::create(
				DelayTime::create(endTurnDelay),
				DelayTime::create(Config::betweenTurnDelay),
				changeState,
				nullptr
			));
			break;
		}
		default:
			break;
	}
}

void StateTurnEnd::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateTurnEnd::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
