#include "StateAIDecideCard.h"

StateAIDecideCard* StateAIDecideCard::create()
{
	StateAIDecideCard* instance = new StateAIDecideCard();

	instance->autorelease();

	return instance;
}

StateAIDecideCard::StateAIDecideCard() : StateBase(GameState::StateType::AIDecideCard)
{
}

StateAIDecideCard::~StateAIDecideCard()
{
}

void StateAIDecideCard::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateAIDecideCard::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);
}

void StateAIDecideCard::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateAIDecideCard::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
