#include "GameState.h"

const std::string GameState::onStateUpdateEvent = "on_state_update_event";

GameState* GameState::create()
{
	GameState* gameState = new GameState();

	gameState->autorelease();

	return gameState;
}

GameState::GameState()
	: stateType(StateType::CoinFlip),
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
	this->playerHand->setRowWidth(Config::handWidth);
	this->enemyHand->setRowWidth(Config::enemyHandWidth);

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
	gameState->stateType = newState;
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GameState::onStateUpdateEvent, gameState);
}