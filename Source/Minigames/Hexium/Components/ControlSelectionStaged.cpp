#include "ControlSelectionStaged.h"

ControlSelectionStaged* ControlSelectionStaged::create()
{
	ControlSelectionStaged* controlSelectionStaged = new ControlSelectionStaged();

	controlSelectionStaged->autorelease();

	return controlSelectionStaged;
}

ControlSelectionStaged::ControlSelectionStaged()
{
}

ControlSelectionStaged::~ControlSelectionStaged()
{
}

void ControlSelectionStaged::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void ControlSelectionStaged::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void ControlSelectionStaged::initializeListeners()
{
}

void ControlSelectionStaged::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	if (gameState->stateType == GameState::StateType::ControlSelectionStaged) {
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

void ControlSelectionStaged::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(ControlSelectionStaged::selectCard, this));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(ControlSelectionStaged::selectCard, this));

	switch (gameState->selectedCard->cardData->cardType)
	{
	case CardData::CardType::Binary:
		gameState->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(ControlSelectionStaged::playSelectedCard, this));
		break;
	case CardData::CardType::Decimal:
		gameState->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(ControlSelectionStaged::playSelectedCard, this));
		break;
	case CardData::CardType::Hexidecimal:
		gameState->playerHexCards->enableRowSelection(CC_CALLBACK_1(ControlSelectionStaged::playSelectedCard, this));
		break;
	case CardData::CardType::Special_SHL:
	case CardData::CardType::Special_SHR:
	case CardData::CardType::Special_FLIP1:
	case CardData::CardType::Special_FLIP2:
	case CardData::CardType::Special_FLIP3:
	case CardData::CardType::Special_FLIP4:
	case CardData::CardType::Special_INV:
		gameState->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(ControlSelectionStaged::playSelectedCard, this));
		gameState->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(ControlSelectionStaged::playSelectedCard, this));
		gameState->playerHexCards->enableRowSelection(CC_CALLBACK_1(ControlSelectionStaged::playSelectedCard, this));
		gameState->enemyBinaryCards->enableRowSelection(CC_CALLBACK_1(ControlSelectionStaged::playSelectedCard, this));
		gameState->enemyDecimalCards->enableRowSelection(CC_CALLBACK_1(ControlSelectionStaged::playSelectedCard, this));
		gameState->enemyHexCards->enableRowSelection(CC_CALLBACK_1(ControlSelectionStaged::playSelectedCard, this));
		break;
	case CardData::CardType::Special_AND:
	case CardData::CardType::Special_OR:
	case CardData::CardType::Special_XOR:
	case CardData::CardType::Special_ADD:
	case CardData::CardType::Special_SUB:
		// These cards require a sacrifice
		gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(ControlSelectionStaged::stageSelectedSacrificeCard, this));
		gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(ControlSelectionStaged::stageSelectedSacrificeCard, this));
		gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(ControlSelectionStaged::stageSelectedSacrificeCard, this));
		break;
	}
}

void ControlSelectionStaged::selectCard(Card* card)
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

void ControlSelectionStaged::stageSelectedSacrificeCard(Card* card)
{
	if (this->activeGameState->selectedCard == nullptr)
	{
		return;
	}

	switch (this->activeGameState->selectedCard->cardData->cardType) {
	case CardData::CardType::Special_AND:
	case CardData::CardType::Special_OR:
	case CardData::CardType::Special_XOR:
	case CardData::CardType::Special_ADD:
	case CardData::CardType::Special_SUB:
		this->activeGameState->stagedSacrifice = card;
		this->activeGameState->stagedSacrificeCardRow = dynamic_cast<CardRow*>(card->getParent());

		GameState::updateState(this->activeGameState, GameState::StateType::ControlSacrificeStaged);
		break;
	}
}

void ControlSelectionStaged::playSelectedCard(CardRow* cardRow)
{
	if (this->activeGameState->selectedCard == nullptr)
	{
		return;
	}

	switch (this->activeGameState->selectedCard->cardData->cardType) {
	case CardData::CardType::Binary:
		this->activeGameState->playerHand->removeCard(this->activeGameState->selectedCard);
		this->activeGameState->playerBinaryCards->insertCard(this->activeGameState->selectedCard, Config::insertDelay);
		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		break;
	case CardData::CardType::Decimal:
		this->activeGameState->playerHand->removeCard(this->activeGameState->selectedCard);
		this->activeGameState->playerDecimalCards->insertCard(this->activeGameState->selectedCard, Config::insertDelay);
		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		break;
	case CardData::CardType::Hexidecimal:
		this->activeGameState->playerHand->removeCard(this->activeGameState->selectedCard);
		this->activeGameState->playerHexCards->insertCard(this->activeGameState->selectedCard, Config::insertDelay);
		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		break;
	case CardData::CardType::Special_SHL:
	case CardData::CardType::Special_SHR:
	case CardData::CardType::Special_FLIP1:
	case CardData::CardType::Special_FLIP2:
	case CardData::CardType::Special_FLIP3:
	case CardData::CardType::Special_FLIP4:
	case CardData::CardType::Special_INV:
		this->activeGameState->playerHand->removeCard(this->activeGameState->selectedCard);
		this->activeGameState->playerGraveyard->insertCardTop(this->activeGameState->selectedCard, true, Config::insertDelay);

		Card::Operation operation = Card::toOperation(this->activeGameState->selectedCard->cardData->cardType, 0);

		for (auto it = cardRow->rowCards->begin(); it != cardRow->rowCards->end(); it++)
		{
			Card* card = *it;

			card->addOperation(operation);
		}

		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		break;
	}

	this->activeGameState->selectedCard = nullptr;
}

void ControlSelectionStaged::aiPerformAction(GameState* gameState)
{
	Card* selectedCard = this->activeGameState->selectedCard;

	if (selectedCard != nullptr)
	{
		switch (selectedCard->cardData->cardType)
		{
		case CardData::CardType::Binary:
			gameState->enemyHand->removeCard(selectedCard);
			gameState->enemyBinaryCards->insertCard(selectedCard, Config::insertDelay);
			GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
			return;
		case CardData::CardType::Decimal:
			gameState->enemyHand->removeCard(selectedCard);
			gameState->enemyDecimalCards->insertCard(selectedCard, Config::insertDelay);
			GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
			return;
		case CardData::CardType::Hexidecimal:
			gameState->enemyHand->removeCard(selectedCard);
			gameState->enemyHexCards->insertCard(selectedCard, Config::insertDelay);
			GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
			return;
		}
	}

	GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
}
