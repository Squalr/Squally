#include "GameState.h"

const std::string GameState::onStateUpdateEvent = "on_state_update_event";

GameState* GameState::create()
{
	GameState* instance = new GameState();

	instance->autorelease();

	return instance;
}

GameState::GameState()
	: stateType(StateType::EmptyState),
	turn(Turn::Player),
	difficulty(Difficulty::Stupid),
	playerLosses(0),
	enemyLosses(0),
	cardReplaceCount(0),
	round(0),
	playerPass(false),
	enemyPass(false),
	stagedSacrifice(nullptr),
	selectedCard(nullptr),
	cardPreviewCallback(nullptr),
	updateStateCallback(nullptr),
	endTurnCallback(nullptr),
	requestAiCallback(nullptr),
	stagedCombineSourceCard(nullptr),
	stagedCombineTargetCard(nullptr)
{
	this->stagedSacrificeTargets = new std::set<Card*>();
	this->playerDeck = Deck::create();
	this->playerHand = CardRow::create(true);
	this->playerGraveyard = Deck::create();
	this->playerBinaryCards = CardRow::create(true);
	this->playerDecimalCards = CardRow::create(true);
	this->playerHexCards = CardRow::create(true);

	this->enemyDeck = Deck::create();
	this->enemyHand = CardRow::create();
	this->enemyGraveyard = Deck::create();
	this->enemyBinaryCards = CardRow::create();
	this->enemyDecimalCards = CardRow::create();
	this->enemyHexCards = CardRow::create();

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
	delete(this->stagedSacrificeTargets);
}

void GameState::updateState(GameState* gameState, StateType newState)
{
	gameState->previousStateType = gameState->stateType;
	gameState->stateType = newState;
	gameState->clearCallbackStates();
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

void GameState::clearCallbackStates()
{
	this->playerHand->setMouseClickCallback(nullptr);
	this->playerHand->setMouseOverCallback(nullptr);
	this->enemyHand->setMouseClickCallback(nullptr);
	this->enemyHand->setMouseOverCallback(nullptr);

	std::vector<CardRow *> rows = this->getAllRows();
	for (auto it = rows.begin(); it != rows.end(); it++)
	{
		CardRow* row = *it;
		row->disableRowSelection();;
	}
}

void GameState::endRound() 
{
	if (this->playerIsWinning()) {
		this->enemyLosses++;
	} else {
		this->playerLosses++;
	}
	this->playerPass = false;
	this->enemyPass = false;

	std::vector<CardRow *> rows = this->getAllRows();
	for (auto it = rows.begin(); it != rows.end(); it++)
	{
		CardRow* row = *it;
		row->clear();
	}

	round++;
}

std::vector<CardRow*> GameState::getAllRows() 
{
	std::vector<CardRow*> enemyRows = this->getEnemyRows();
	std::vector<CardRow*> playerRows = this->getPlayerRows();
	enemyRows.insert(enemyRows.end(), playerRows.begin(), playerRows.end());
	return enemyRows;
}

std::vector<CardRow*> GameState::getEnemyRows() 
{
	std::vector<CardRow*> cardRows;
	cardRows.emplace_back(this->playerBinaryCards);
	cardRows.emplace_back(this->playerDecimalCards);
	cardRows.emplace_back(this->playerHexCards);
	return cardRows;
}

std::vector<CardRow*> GameState::getPlayerRows() 
{
	std::vector<CardRow*> cardRows;
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

bool GameState::enemyIsWinning()
{
	return this->getEnemyTotal() > this->getPlayerTotal();
}

bool GameState::playerIsWinning()
{
	return this->getPlayerTotal() > this->getEnemyTotal();
}