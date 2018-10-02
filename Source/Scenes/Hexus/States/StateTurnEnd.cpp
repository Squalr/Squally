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

	this->activeGameState = gameState;

	gameState->clearCallbackStates();
	this->endTurn(gameState);
}

void StateTurnEnd::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateTurnEnd::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}

void StateTurnEnd::endTurn(GameState* gameState)
{
	float endTurnDelay = Config::endTurnDelay;

	// If both players pass than we end the round
	if (gameState->playerPass && gameState->enemyPass) {
		CallFunc* changeState = CallFunc::create([gameState] {
			GameState::updateState(gameState, GameState::StateType::GameEnd);
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
	if (gameState->playerPass) {
		endTurnDelay = Config::enemyEndTurnDelay;
		gameState->turn = GameState::Turn::Enemy;
		CallFunc* changeState = CallFunc::create([gameState] {
			GameState::updateState(gameState, GameState::StateType::TurnEnd);
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
	if (gameState->enemyPass) {
		gameState->turn = GameState::Turn::Player;
		CallFunc* changeState = CallFunc::create([gameState] {
			GameState::updateState(gameState, GameState::StateType::TurnEnd);
		});

		this->runAction(Sequence::create(
			DelayTime::create(endTurnDelay),
			DelayTime::create(Config::betweenTurnDelay),
			changeState,
			nullptr
		));
		return;
	}

	//  If no one has passed we alternate turns
	switch (gameState->turn)
	{
	case GameState::Turn::Enemy:
		endTurnDelay = Config::enemyEndTurnDelay;
		gameState->turn = GameState::Turn::Player;
		break;
	case GameState::Turn::Player:
		gameState->turn = GameState::Turn::Enemy;
		break;
	}

	CallFunc* changeState = CallFunc::create([gameState] {
		GameState::updateState(gameState, GameState::StateType::TurnEnd);
	});

	this->runAction(Sequence::create(
		DelayTime::create(endTurnDelay),
		DelayTime::create(Config::betweenTurnDelay),
		changeState,
		nullptr
	));
}
