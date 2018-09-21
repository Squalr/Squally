#include "ControlNeutral.h"

ControlNeutral* ControlNeutral::create()
{
	ControlNeutral* instance = new ControlNeutral();

	instance->autorelease();

	return instance;
}

ControlNeutral::ControlNeutral()
{
}

ControlNeutral::~ControlNeutral()
{
}

void ControlNeutral::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	if (gameState->stateType == GameState::StateType::ControlNeutral) {
		switch (gameState->turn)
		{
		case GameState::Turn::Player:
			this->initializeCallbacks(gameState);
			this->activeGameState->playerHand->enableRowCardInteraction();
			break;
		case GameState::Turn::Enemy:
			this->aiDoSelection(gameState);
			this->activeGameState->playerHand->disableRowCardInteraction();
			break;
		}
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

void ControlNeutral::aiDoSelection(GameState* gameState)
{
	bool selectionMade = false;

	this->activeGameState->selectedCard = nullptr;

	for (auto it = gameState->enemyHand->rowCards->begin(); it != gameState->enemyHand->rowCards->end(); it++)
	{
		Card* card = *it;

		switch (card->cardData->cardType)
		{
		case CardData::CardType::Binary:
		case CardData::CardType::Decimal:
		case CardData::CardType::Hexidecimal:
			this->activeGameState->selectedCard = card;
			selectionMade = true;
			break;
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		case CardData::CardType::Special_INV:
			this->activeGameState->selectedCard = card;
			selectionMade = true;
			break;
		/*
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
			this->activeGameState->selectedCard = card;
			selectionMade = true;
			break;
		*/
		default: 
			break;
		}

		if (selectionMade)
		{
			break;
		}
	}

	if (selectionMade) {
		GameState::updateState(this->activeGameState, GameState::StateType::ControlSelectionStaged);
	} else {
		this->activeGameState->enemyPass = true;
		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
	}

}
