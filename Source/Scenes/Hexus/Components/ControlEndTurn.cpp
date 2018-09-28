#include "ControlEndTurn.h"

ControlEndTurn* ControlEndTurn::create()
{
	ControlEndTurn* instance = new ControlEndTurn();

	instance->autorelease();

	return instance;
}

ControlEndTurn::ControlEndTurn()
{
}

ControlEndTurn::~ControlEndTurn()
{
}

void ControlEndTurn::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	if (gameState->stateType == GameState::StateType::EndTurn) {
		gameState->clearCallbackStates();
		this->endTurn(gameState);
	}
}

void ControlEndTurn::endTurn(GameState* gameState)
{
	float endTurnDelay = Config::endTurnDelay;

	// If both players pass than we end the round
	if (gameState->playerPass && gameState->enemyPass) {
		CallFunc* changeState = CallFunc::create([gameState] {
			GameState::updateState(gameState, GameState::StateType::Score);
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
			GameState::updateState(gameState, GameState::StateType::TurnBanner);
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
			GameState::updateState(gameState, GameState::StateType::TurnBanner);
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
		GameState::updateState(gameState, GameState::StateType::TurnBanner);
	});

	this->runAction(Sequence::create(
		DelayTime::create(endTurnDelay),
		DelayTime::create(Config::betweenTurnDelay),
		changeState,
		nullptr
	));
}
