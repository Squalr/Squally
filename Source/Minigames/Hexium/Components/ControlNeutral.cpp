#include "ControlNeutral.h"

ControlNeutral* ControlNeutral::create()
{
	ControlNeutral* controlNeutral = new ControlNeutral();

	controlNeutral->autorelease();

	return controlNeutral;
}

ControlNeutral::ControlNeutral()
{
}

ControlNeutral::~ControlNeutral()
{
}

void ControlNeutral::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void ControlNeutral::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void ControlNeutral::initializeListeners()
{
}

void ControlNeutral::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	if (gameState->stateType == GameState::StateType::ControlNeutral) {
		gameState->clearCallbackStates();
		this->initializeCallbacks(gameState);
	}
}

void ControlNeutral::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(ControlNeutral::selectCard, this));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(ControlNeutral::selectCard, this));
}

void ControlNeutral::selectCard(Card* card)
{
	this->activeGameState->selectedCard = card;
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

	GameState::updateState(this->activeGameState, GameState::StateType::ControlSelectionStaged);
}
