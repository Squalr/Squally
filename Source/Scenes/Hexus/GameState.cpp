#include "GameState.h"

const std::string GameState::requestStateUpdateEvent = "EVENT_HEXUS_REQUEST_UPDATE_STATE";
const std::string GameState::beforeStateUpdateEvent = "EVENT_HEXUS_BEFORE_UPDATE_STATE";
const std::string GameState::onStateUpdateEvent = "EVENT_HEXUS_ON_UPDATE_STATE";

GameState* GameState::create()
{
	GameState* instance = new GameState();

	instance->autorelease();

	return instance;
}

GameState::GameState()
	: stateType(StateType::EmptyState),
	turn(Turn::Player),
	difficulty(HexusOpponentData::Strategy::Random),
	tutorialMode(StateOverride::TutorialMode::NoTutorial),
	playerLosses(0),
	enemyLosses(0),
	cardReplaceCount(0),
	isRepeatingSameTurn(false),
	playerPassed(false),
	enemyPassed(false),
	turnNumber(0),
	playableCardsThisTurn(0),
	playerCardsDrawnNextRound(0),
	enemyCardsDrawnNextRound(0),
	roundNumber(0),
	selectedHandCard(nullptr),
	selectedRow(nullptr),
	cardPreviewCallback(nullptr),
	updateStateCallback(nullptr),
	endTurnCallback(nullptr),
	requestAiCallback(nullptr),
	selectedSourceCard(nullptr),
	selectedDestinationCard(nullptr)
{
	this->playerDeck = Deck::create();
	this->playerHand = CardRow::create(true);
	this->playerGraveyard = Deck::create();
	this->playerBinaryCards = CardRow::create(true);
	this->playerDecimalCards = CardRow::create(true);
	this->playerHexCards = CardRow::create(true);

	this->enemyDeck = Deck::create();
	this->enemyHand = CardRow::create(false);
	this->enemyGraveyard = Deck::create();
	this->enemyBinaryCards = CardRow::create(false);
	this->enemyDecimalCards = CardRow::create(false);
	this->enemyHexCards = CardRow::create(false);

	this->enemyHand->setVisible(false);
	this->playerHand->setRowWidth(Config::handWidth, 0.0f);
	this->enemyHand->setRowWidth(Config::enemyHandWidth, 0.0f);

	this->addChild(this->enemyGraveyard);
	this->addChild(this->enemyDeck);
	this->addChild(this->enemyHexCards);
	this->addChild(this->enemyDecimalCards);
	this->addChild(this->enemyBinaryCards);
	this->addChild(this->enemyHand);

	this->addChild(this->playerGraveyard);
	this->addChild(this->playerDeck);
	this->addChild(this->playerHexCards);
	this->addChild(this->playerDecimalCards);
	this->addChild(this->playerBinaryCards);
	this->addChild(this->playerHand);
}

GameState::~GameState()
{
}

void GameState::updateState(GameState* gameState, StateType newState)
{
	gameState->previousStateType = gameState->stateType;
	gameState->stateType = newState;
	gameState->clearInteraction();

	switch (newState)
	{
		case StateType::GameStart:
		{
			gameState->gameStartTime = std::chrono::high_resolution_clock::now();
			break;
		}
		case StateType::GameEnd:
		{
			gameState->gameEndTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = gameState->gameEndTime - gameState->gameStartTime;
			gameState->gameDurationInSeconds = (int)(elapsed.count());
			break;
		}
		default:
		{
			break;
		}
	}

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GameState::requestStateUpdateEvent, gameState);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GameState::beforeStateUpdateEvent, gameState);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GameState::onStateUpdateEvent, gameState);
}

void GameState::initializePositions()
{
	SmartNode::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemyGraveyard->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f + Config::graveyardOffsetY);
	this->playerGraveyard->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::graveyardOffsetX, visibleSize.height / 2.0f - Config::graveyardOffsetY);

	this->playerDeck->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f - Config::deckOffsetY);
	this->enemyDeck->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX, visibleSize.height / 2.0f + Config::deckOffsetY);

	this->playerHand->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - Config::handOffsetY);
	this->playerBinaryCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::binaryRowOffsetY);
	this->playerDecimalCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::decimalRowOffsetY);
	this->playerHexCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY - Config::hexRowOffsetY);

	this->enemyHand->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::handOffsetY + 256.0f);
	this->enemyBinaryCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::binaryRowOffsetY);
	this->enemyDecimalCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::decimalRowOffsetY);
	this->enemyHexCards->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::boardCenterOffsetY + Config::hexRowOffsetY);
}

void GameState::clearInteraction()
{
	this->playerHand->setMouseClickCallback(nullptr);
	this->playerHand->setMouseOverCallback(nullptr);
	this->enemyHand->setMouseClickCallback(nullptr);
	this->enemyHand->setMouseOverCallback(nullptr);

	this->enemyHand->disableRowSelection();
	this->enemyHand->disableRowCardSelection();
	this->enemyHand->disableRowCardInteraction();
	this->playerHand->disableRowSelection();
	this->playerHand->disableRowCardSelection();
	this->playerHand->disableRowCardInteraction();

	std::vector<CardRow*> rows = this->getAllRows();

	for (auto it = rows.begin(); it != rows.end(); it++)
	{
		CardRow* row = *it;

		row->disableRowSelection();
		row->disableRowCardSelection();
		row->disableRowCardInteraction();
	}
}

void GameState::removeFieldCards()
{
	std::vector<CardRow *> rows = this->getAllRows();

	for (auto it = rows.begin(); it != rows.end(); it++)
	{
		CardRow* row = *it;
		row->clear();
	}

	roundNumber++;
}

std::vector<Card*> GameState::getAllCards() 
{
	std::vector<CardRow*> rows = this->getAllRows();
	std::vector<Card*> cards;

	for (auto it = rows.begin(); it != rows.end(); it++)
	{
		CardRow* row = *it;

		for (auto it = row->rowCards.begin(); it != row->rowCards.end(); it++)
		{
			Card* card = *it;
			cards.emplace_back(card);
		}
	}

	return cards;
}

std::vector<Card*> GameState::getEnemyCards() 
{
	std::vector<CardRow*> rows = this->getEnemyRows();
	std::vector<Card*> cards;

	for (auto it = rows.begin(); it != rows.end(); it++)
	{
		CardRow* row = *it;

		for (auto it = row->rowCards.begin(); it != row->rowCards.end(); it++)
		{
			Card* card = *it;
			cards.emplace_back(card);
		}
	}

	return cards;
}

std::vector<Card*> GameState::getPlayerCards() 
{
	std::vector<CardRow*> rows = this->getPlayerRows();
	std::vector<Card*> cards;

	for (auto it = rows.begin(); it != rows.end(); it++)
	{
		CardRow* row = *it;

		for (auto it = row->rowCards.begin(); it != row->rowCards.end(); it++)
		{
			Card* card = *it;
			cards.emplace_back(card);
		}
	}

	return cards;
}

std::vector<CardRow*> GameState::getAllRows() 
{
	std::vector<CardRow*> rows = std::vector<CardRow*>();
	std::vector<CardRow*> enemyRows = this->getEnemyRows();
	std::vector<CardRow*> playerRows = this->getPlayerRows();

	rows.insert(rows.end(), enemyRows.begin(), enemyRows.end());
	rows.insert(rows.end(), playerRows.begin(), playerRows.end());

	return rows;
}

std::vector<CardRow*> GameState::getEnemyRows() 
{
	std::vector<CardRow*> cardRows;

	cardRows.emplace_back(this->enemyBinaryCards);
	cardRows.emplace_back(this->enemyDecimalCards);
	cardRows.emplace_back(this->enemyHexCards);

	return cardRows;
}

std::vector<CardRow*> GameState::getPlayerRows() 
{
	std::vector<CardRow*> cardRows = std::vector<CardRow*>();

	cardRows.emplace_back(this->playerBinaryCards);
	cardRows.emplace_back(this->playerDecimalCards);
	cardRows.emplace_back(this->playerHexCards);

	return cardRows;
}

int GameState::getPlayerTotal()
{
	int total = 0;

	total += this->playerBinaryCards->getRowAttack();
	total += this->playerDecimalCards->getRowAttack();
	total += this->playerHexCards->getRowAttack();

	return total;
}

int GameState::getEnemyTotal()
{
	int total = 0;

	total += this->enemyBinaryCards->getRowAttack();
	total += this->enemyDecimalCards->getRowAttack();
	total += this->enemyHexCards->getRowAttack();

	return total;
}

int GameState::getCardCount()
{
	return this->getPlayerCardCount() + this->getEnemyCardCount();
}

int GameState::getPlayerCardCount()
{
	int total = 0;

	total += this->playerBinaryCards->getCardCount();
	total += this->playerDecimalCards->getCardCount();
	total += this->playerHexCards->getCardCount();

	return total;
}

int GameState::getEnemyCardCount()
{
	int total = 0;

	total += this->enemyBinaryCards->getCardCount();
	total += this->enemyDecimalCards->getCardCount();
	total += this->enemyHexCards->getCardCount();

	return total;
}

bool GameState::isRoundTied()
{
	return this->getEnemyTotal() == this->getPlayerTotal();
}

bool GameState::isEnemyWinningRound()
{
	return this->getEnemyTotal() > this->getPlayerTotal();
}

bool GameState::isPlayerWinningRound()
{
	return this->getPlayerTotal() > this->getEnemyTotal();
}

bool GameState::isPlayerLastStandCondition()
{
	return (this->isPlayerWinningRound() && !this->enemyPassed);
}

bool GameState::isPlayerClaimVictoryCondition()
{
	return (this->isPlayerWinningRound() && this->enemyPassed);
}

bool GameState::isPlayerPassCondition()
{
	return (!this->isPlayerLastStandCondition() && !this->isPlayerClaimVictoryCondition());
}

bool GameState::isEnemyLastStandCondition()
{
	return (this->isEnemyWinningRound() && !this->playerPassed);
}

bool GameState::isEnemyClaimVictoryCondition()
{
	return (this->isEnemyWinningRound() && this->playerPassed);
}

bool GameState::isEnemyPassCondition()
{
	return (!this->isEnemyLastStandCondition() && !this->isEnemyClaimVictoryCondition());
}
