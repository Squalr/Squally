#include "StateLoadInitialState.h"

StateLoadInitialState* StateLoadInitialState::create()
{
	StateLoadInitialState* instance = new StateLoadInitialState();

	instance->autorelease();

	return instance;
}

StateLoadInitialState::StateLoadInitialState() : StateBase(GameState::StateType::LoadInitialState)
{
}

StateLoadInitialState::~StateLoadInitialState()
{
}

void StateLoadInitialState::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateLoadInitialState::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	this->loadStateOverrides(gameState, gameState->opponentData->stateOverride);
}

void StateLoadInitialState::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateLoadInitialState::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
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

	gameState->enemyPassed = stateOverride->enemyPassed;
	gameState->playerPassed = stateOverride->playerPassed;

	gameState->playerLosses = stateOverride->playerLosses;
	gameState->enemyLosses = stateOverride->enemyLosses;

	// Load player cards
	for (auto it = stateOverride->playerHand.begin(); it != stateOverride->playerHand.end(); it++)
	{
		gameState->playerHand->insertCard(Card::create(Card::CardStyle::Earth, *it), 0.0f);
	}

	for (auto it = stateOverride->playerDeck.begin(); it != stateOverride->playerDeck.end(); it++)
	{
		gameState->playerDeck->insertCardBottom(Card::create(Card::CardStyle::Earth, *it), false, 0.0f);
	}

	for (auto it = stateOverride->playerBinaryCards.begin(); it != stateOverride->playerBinaryCards.end(); it++)
	{
		gameState->playerBinaryCards->insertCard(Card::create(Card::CardStyle::Earth, *it), 0.0f);
	}

	for (auto it = stateOverride->playerDecimalCards.begin(); it != stateOverride->playerDecimalCards.end(); it++)
	{
		gameState->playerDecimalCards->insertCard(Card::create(Card::CardStyle::Earth, *it), 0.0f);
	}

	for (auto it = stateOverride->playerHexCards.begin(); it != stateOverride->playerHexCards.end(); it++)
	{
		gameState->playerHexCards->insertCard(Card::create(Card::CardStyle::Earth, *it), 0.0f);
	}

	// Load enemy cards
	for (auto it = stateOverride->enemyHand.begin(); it != stateOverride->enemyHand.end(); it++)
	{
		gameState->enemyHand->insertCard(Card::create(Card::CardStyle::Shadow, *it), 0.0f);
	}

	for (auto it = stateOverride->enemyDeck.begin(); it != stateOverride->enemyDeck.end(); it++)
	{
		gameState->enemyDeck->insertCardBottom(Card::create(Card::CardStyle::Shadow, *it), false, 0.0f);
	}

	for (auto it = stateOverride->enemyBinaryCards.begin(); it != stateOverride->enemyBinaryCards.end(); it++)
	{
		gameState->enemyBinaryCards->insertCard(Card::create(Card::CardStyle::Shadow, *it), 0.0f);
	}

	for (auto it = stateOverride->enemyDecimalCards.begin(); it != stateOverride->enemyDecimalCards.end(); it++)
	{
		gameState->enemyDecimalCards->insertCard(Card::create(Card::CardStyle::Shadow, *it), 0.0f);
	}

	for (auto it = stateOverride->enemyHexCards.begin(); it != stateOverride->enemyHexCards.end(); it++)
	{
		gameState->enemyHexCards->insertCard(Card::create(Card::CardStyle::Shadow, *it), 0.0f);
	}

	if (stateOverride->playersTurn)
	{
		gameState->updateState(gameState, GameState::StateType::PlayerTurnStart);
	}
	else
	{
		gameState->updateState(gameState, GameState::StateType::OpponentTurnStart);
	}
}
