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
		switch (gameState->turn)
		{
		case GameState::Turn::Player:
			this->initializeCallbacks(gameState);
			break;
		case GameState::Turn::Enemy:
			this->aiPerformAction(gameState);
			break;
		}
	}
}

void ControlSacrificeStaged::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(ControlSacrificeStaged::selectCard, this));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(ControlSacrificeStaged::selectCard, this));

	gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(ControlSacrificeStaged::stageSacrificeTarget, this));
	gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(ControlSacrificeStaged::stageSacrificeTarget, this));
	gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(ControlSacrificeStaged::stageSacrificeTarget, this));

	gameState->stagedSacrificeTargets->clear();
	gameState->stagedSacrifice->setFocusTint(Color3B::RED);
	gameState->stagedSacrifice->focus();
	gameState->stagedSacrifice->setMouseClickCallback(nullptr);
}

void ControlSacrificeStaged::aiPerformAction(GameState* gameState)
{

}

void ControlSacrificeStaged::selectCard(Card* card)
{
	// Unstage/deselect card if clicking the active card
	if (card == this->activeGameState->selectedCard)
	{
		this->activeGameState->selectedCard->stopAllActions();
		this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position));
		GameState::updateState(this->activeGameState, GameState::StateType::ControlNeutral);
		return;
	}

	// Otherwise this is just a selection/re-staging of a new card
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position));

	this->activeGameState->selectedCard = card;
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

	// Transition to the same state (re-initialize things)
	GameState::updateState(this->activeGameState, GameState::StateType::ControlSelectionStaged);
}


void ControlSacrificeStaged::stageSacrificeTarget(Card* card)
{
	switch (this->activeGameState->selectedCard->cardData->cardType) {
	case CardData::CardType::Special_AND:
	case CardData::CardType::Special_OR:
	case CardData::CardType::Special_XOR:
	case CardData::CardType::Special_ADD:
	case CardData::CardType::Special_SUB:
		card->focus();
		card->setFocusTint(Color3B::BLUE);
		this->activeGameState->stagedSacrificeTargets->insert(card);
		break;
	}

	switch (this->activeGameState->selectedCard->cardData->cardType) {
	case CardData::CardType::Special_AND:
	case CardData::CardType::Special_OR:
	case CardData::CardType::Special_XOR:
	case CardData::CardType::Special_ADD:
	case CardData::CardType::Special_SUB:
		if (this->activeGameState->stagedSacrificeTargets->size() >= 2)
		{
			this->activeGameState->stagedSacrifice->unfocus();
			this->activeGameState->playerHand->removeCard(this->activeGameState->selectedCard);
			this->activeGameState->playerGraveyard->insertCardTop(this->activeGameState->selectedCard, true, Config::insertDelay);

			this->activeGameState->stagedSacrificeCardRow->removeCard(this->activeGameState->stagedSacrifice);
			this->activeGameState->playerGraveyard->insertCardTop(this->activeGameState->stagedSacrifice, true, Config::insertDelay);

			Card::Operation operation = Card::toOperation(this->activeGameState->selectedCard->cardData->cardType, this->activeGameState->stagedSacrifice->getAttack());

			for (auto it = this->activeGameState->stagedSacrificeTargets->begin(); it != this->activeGameState->stagedSacrificeTargets->end(); *it++)
			{
				Card* target = *it;

				target->addOperation(operation);
			}

			GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		}
		break;
	}

}