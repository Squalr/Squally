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
		gameState->clearCallbackStates();
		this->initializeCallbacks(gameState);
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
	case CardData::CardType::Special:
		//gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(ControlSelectionStaged::stageSelectedSacrificeCard, this));
		//gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(ControlSelectionStaged::stageSelectedSacrificeCard, this));
		//gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(ControlSelectionStaged::stageSelectedSacrificeCard, this));
		break;
	}

	/*
	gameState->playerBinaryCards->setMouseClickCallback(CC_CALLBACK_1(ControlSelectionStaged::onRowCardClick, this));
	gameState->playerDecimalCards->setMouseClickCallback(CC_CALLBACK_1(ControlSelectionStaged::onRowCardClick, this));
	gameState->playerHexCards->setMouseClickCallback(CC_CALLBACK_1(ControlSelectionStaged::onRowCardClick, this));

	gameState->enemyBinaryCards->setMouseClickCallback(CC_CALLBACK_1(ControlSelectionStaged::onRowCardClick, this));
	gameState->enemyDecimalCards->setMouseClickCallback(CC_CALLBACK_1(ControlSelectionStaged::onRowCardClick, this));
	gameState->enemyHexCards->setMouseClickCallback(CC_CALLBACK_1(ControlSelectionStaged::onRowCardClick, this));
	*/
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

/*
void ControlSelectionStaged::cancelCurrentAction(bool clearSelectedCard)
{
	if (this->selectedCard != nullptr)
	{
		switch (this->selectedCard->cardData->cardType)
		{
		case CardData::CardType::Binary:
			this->playerBinaryCards->disableRowSelection();
			break;
		case CardData::CardType::Decimal:
			this->playerDecimalCards->disableRowSelection();
			break;
		case CardData::CardType::Hexidecimal:
			this->playerHexCards->disableRowSelection();
			break;
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		case CardData::CardType::Special_INV:
			this->playerBinaryCards->disableRowSelection();
			this->playerDecimalCards->disableRowSelection();
			this->playerHexCards->disableRowSelection();
			this->enemyBinaryCards->disableRowSelection();
			this->enemyDecimalCards->disableRowSelection();
			this->enemyHexCards->disableRowSelection();
			break;
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
		case CardData::CardType::Special:
			this->playerBinaryCards->disableRowSelection();
			this->playerDecimalCards->disableRowSelection();
			this->playerHexCards->disableRowSelection();
			break;
		}

		if (clearSelectedCard)
		{
			this->selectCard(nullptr);
		}
	}
}

void ControlSelectionStaged::stageSelectedSacrificeCard(Card* card)
{
	if (this->selectedCard == nullptr)
	{
		return;
	}

	switch (this->selectedCard->cardData->cardType) {
	case CardData::CardType::Special_AND:
	case CardData::CardType::Special_OR:
	case CardData::CardType::Special_XOR:
	case CardData::CardType::Special_ADD:
	case CardData::CardType::Special_SUB:
		this->stagedSacrifice = card;
		this->playerHand->removeCard(this->selectedCard);
		this->selectedCard->disableInteraction();
		this->playerGraveyard->insertCardTop(this->selectedCard, true, Config::insertDelay);

		Card::Operation operation = Card::toOperation(this->selectedCard->cardData->cardType, 0);

		for (auto it = cardRow->rowCards->begin(); it != cardRow->rowCards->end(); it++)
		{
			Card* card = *it;

			card->addOperation(operation);
		}

		this->playerBinaryCards->disableRowSelection();
		this->playerDecimalCards->disableRowSelection();
		this->playerHexCards->disableRowSelection();
		this->enemyBinaryCards->disableRowSelection();
		this->enemyDecimalCards->disableRowSelection();
		this->enemyHexCards->disableRowSelection();
		this->endTurn();
		break;
	}

	this->selectedCard = nullptr;
}

void ControlSelectionStaged::gameStart(Deck* startPlayerDeck, Deck* startEnemyDeck)
{

	startPlayerDeck->copyTo(this->playerDeck);
	startEnemyDeck->copyTo(this->enemyDeck);


	this->disableUserInteraction();
	this->randomizeTurn();
}

void ControlSelectionStaged::giveControl()
{
	switch (this->turn)
	{
	case Turn::Enemy:
		if (this->requestAiCallback != nullptr) {
			this->requestAiCallback(this);
		}
		break;
	case Turn::Player:
	default:
		this->enableUserInteraction();
		break;
	}
}

*/
