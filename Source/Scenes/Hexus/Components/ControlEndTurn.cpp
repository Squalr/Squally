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

void ControlEndTurn::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void ControlEndTurn::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void ControlEndTurn::initializeListeners()
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

	switch (gameState->turn)
	{
	case GameState::Turn::Enemy:
		endTurnDelay = Config::enemyEndTurnDelay;
		gameState->turn = GameState::Turn::Player;
		break;
	case GameState::Turn::Player:
	default:
		gameState->turn = GameState::Turn::Enemy;
		break;
	}

	CallFunc* changeState = CallFunc::create([gameState] {
		GameState::updateState(gameState, GameState::StateType::Draw);
	});

	this->runAction(Sequence::create(
		DelayTime::create(endTurnDelay),
		DelayTime::create(Config::betweenTurnDelay),
		changeState,
		nullptr
	));
}
