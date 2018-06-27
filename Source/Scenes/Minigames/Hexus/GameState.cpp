#include "GameState.h"

const std::string GameState::onStateUpdateEvent = "on_state_update_event";

GameState* GameState::create()
{
	GameState* gameState = new GameState();

	gameState->autorelease();

	return gameState;
}

GameState::GameState()
	: stateType(StateType::EmptyState),
	turn(Turn::Player),
	difficulty(Difficulty::Stupid),
	playerLosses(0),
	enemyLosses(0),
	stagedSacrifice(nullptr),
	selectedCard(nullptr),
	cardPreviewCallback(nullptr),
	updateStateCallback(nullptr),
	endTurnCallback(nullptr),
	requestAiCallback(nullptr)
{
	this->stagedSacrificeTargets = new std::set<Card*>();
	this->playerDeck = Deck::create();
	this->playerHand = CardRow::create();
	this->playerGraveyard = Deck::create();
	this->playerBinaryCards = CardRow::create();
	this->playerDecimalCards = CardRow::create();
	this->playerHexCards = CardRow::create();

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

void GameState::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void GameState::initializePositions()
{
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

void GameState::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void GameState::clearCallbackStates()
{
	this->playerHand->setMouseClickCallback(nullptr);
	this->playerHand->setMouseOverCallback(nullptr);
	this->enemyHand->setMouseClickCallback(nullptr);
	this->enemyHand->setMouseOverCallback(nullptr);

	this->playerBinaryCards->disableRowSelection();
	this->playerDecimalCards->disableRowSelection();
	this->playerHexCards->disableRowSelection();
	this->enemyBinaryCards->disableRowSelection();
	this->enemyDecimalCards->disableRowSelection();
	this->enemyHexCards->disableRowSelection();

	this->playerBinaryCards->disableRowCardSelection();
	this->playerDecimalCards->disableRowCardSelection();
	this->playerHexCards->disableRowCardSelection();
	this->enemyBinaryCards->disableRowCardSelection();
	this->enemyDecimalCards->disableRowCardSelection();
	this->enemyHexCards->disableRowCardSelection();
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