#include "ControlSacrificeStaged.h"

ControlSacrificeStaged* ControlSacrificeStaged::create()
{
	ControlSacrificeStaged* controlSacrificeStaged = new ControlSacrificeStaged();

	controlSacrificeStaged->autorelease();

	return controlSacrificeStaged;
}

ControlSacrificeStaged::ControlSacrificeStaged()
{
}

ControlSacrificeStaged::~ControlSacrificeStaged()
{
}

void ControlSacrificeStaged::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void ControlSacrificeStaged::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void ControlSacrificeStaged::initializeListeners()
{
}

void ControlSacrificeStaged::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	if (gameState->stateType == GameState::StateType::ControlSacrificeStaged) {
		gameState->clearCallbackStates();
		this->initializeCallbacks(gameState);
	}
}

void ControlSacrificeStaged::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(ControlSacrificeStaged::selectCard, this));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(ControlSacrificeStaged::selectCard, this));
}

void ControlSacrificeStaged::selectCard(Card* card)
{
	if (this->activeGameState->selectedCard != nullptr)
	{
		this->activeGameState->selectedCard->stopAllActions();
		this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position));
	}

	this->activeGameState->selectedCard = card;
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));
}
