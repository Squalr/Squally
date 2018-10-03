#include "StatePlayCard.h"

StatePlayCard* StatePlayCard::create()
{
	StatePlayCard* instance = new StatePlayCard();

	instance->autorelease();

	return instance;
}

StatePlayCard::StatePlayCard() : StateBase(GameState::StateType::PlayCard)
{
}

StatePlayCard::~StatePlayCard()
{
}

void StatePlayCard::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StatePlayCard::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	GameState::updateState(gameState, GameState::StateType::TurnEnd);
}

void StatePlayCard::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StatePlayCard::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
