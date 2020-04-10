#include "StateLoadInitialState.h"

#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Deck.h"

using namespace cocos2d;

StateLoadInitialState* StateLoadInitialState::create()
{
	StateLoadInitialState* instance = new StateLoadInitialState();

	instance->autorelease();

	return instance;
}

StateLoadInitialState::StateLoadInitialState() : super(GameState::StateType::LoadInitialState)
{
}

StateLoadInitialState::~StateLoadInitialState()
{
}

void StateLoadInitialState::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateLoadInitialState::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	this->loadStateOverrides(gameState, gameState->opponentData->stateOverride);
}

void StateLoadInitialState::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateLoadInitialState::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}

void StateLoadInitialState::loadStateOverrides(GameState* gameState, StateOverride* stateOverride)
{
	if (stateOverride == nullptr)
	{
		return;
	}

	// Destroy existing state -- just the deck needs to be cleared because this method should be called at the start of the game
	gameState->playerDeck->clear();
	gameState->enemyDeck->clear();
	gameState->playerGraveyard->clear();
	gameState->enemyGraveyard->clear();

	gameState->enemyPassed = stateOverride->enemyPassed;
	gameState->playerPassed = stateOverride->playerPassed;

	gameState->playerLosses = stateOverride->playerLosses;
	gameState->enemyLosses = stateOverride->enemyLosses;

	gameState->showChallengeBanner = stateOverride->showChallengeBanner;

	// Load player cards
	for (auto next : stateOverride->playerHand)
	{
		gameState->playerHand->insertCard(Card::create(Card::CardStyle::Earth, next, true), 0.0f, false);
	}

	for (auto next : stateOverride->playerDeck)
	{
		gameState->playerDeck->insertCardBottom(Card::create(Card::CardStyle::Earth, next, true), false, 0.0f, false);
	}

	for (auto next : stateOverride->playerBinaryCards)
	{
		gameState->playerBinaryCards->insertCard(Card::create(Card::CardStyle::Earth, next, true), 0.0f, false);
	}

	for (auto next : stateOverride->playerDecimalCards)
	{
		gameState->playerDecimalCards->insertCard(Card::create(Card::CardStyle::Earth, next, true), 0.0f, false);
	}

	for (auto next : stateOverride->playerHexCards)
	{
		gameState->playerHexCards->insertCard(Card::create(Card::CardStyle::Earth, next, true), 0.0f, false);
	}

	// Load enemy cards
	for (auto next : stateOverride->enemyHand)
	{
		gameState->enemyHand->insertCard(Card::create(Card::CardStyle::Shadow, next, false), 0.0f, false);
	}

	for (auto next : stateOverride->enemyDeck)
	{
		gameState->enemyDeck->insertCardBottom(Card::create(Card::CardStyle::Shadow, next, false), false, 0.0f, false);
	}

	for (auto next : stateOverride->enemyBinaryCards)
	{
		gameState->enemyBinaryCards->insertCard(Card::create(Card::CardStyle::Shadow, next, false), 0.0f, false);
	}

	for (auto next : stateOverride->enemyDecimalCards)
	{
		gameState->enemyDecimalCards->insertCard(Card::create(Card::CardStyle::Shadow, next, false), 0.0f, false);
	}

	for (auto next : stateOverride->enemyHexCards)
	{
		gameState->enemyHexCards->insertCard(Card::create(Card::CardStyle::Shadow, next, false), 0.0f, false);
	}

	if (stateOverride->playersTurn)
	{
		gameState->turn = GameState::Turn::Player;
		gameState->updateState(gameState, GameState::StateType::PlayerTurnStart);
	}
	else
	{
		gameState->turn = GameState::Turn::Enemy;
		gameState->updateState(gameState, GameState::StateType::OpponentTurnStart);
	}
}
