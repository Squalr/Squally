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
}

void StateTurnEnd::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	gameState->turnNumber++;
	gameState->clearInteraction();

	float endTurnDelay = Config::endTurnDelay;
	gameState->isRepeatingSameTurn = false;
	gameState->selectedRow = nullptr;
	gameState->stagedCombineCardRow = nullptr;
	gameState->stagedCombineSourceCard = nullptr;
	gameState->stagedCombineTargetCard = nullptr;

	// If both players activated last stand / passed than we end the round
	if ((gameState->playerLastStanded || gameState->playerPassed) && (gameState->enemyLastStanded || gameState->enemyPassed))
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

	// If the player activated last stand it is the enemies turn
	if (gameState->playerLastStanded)
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

	// If the enemy activated last stand it is the players turn
	if (gameState->enemyLastStanded)
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
