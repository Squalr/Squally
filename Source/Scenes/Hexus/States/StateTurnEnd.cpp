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

	gameState->clearInteraction();

	float endTurnDelay = Config::endTurnDelay;

	// If both players pass than we end the round
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

	// If the player passes it is the enemies turn
	if (gameState->playerPassed)
	{
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

	// If the enemy passes it is the players turn
	if (gameState->enemyPassed)
	{
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

	// If no one has passed we alternate turns
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
