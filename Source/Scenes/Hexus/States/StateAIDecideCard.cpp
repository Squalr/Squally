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

	gameState->selectedCard = nullptr;

	// For now, we greedily select the first playable card
	for (auto it = gameState->enemyHand->rowCards->begin(); it != gameState->enemyHand->rowCards->end(); it++)
	{
		gameState->selectedCard = *it;
		break;
	}

	// ERROR - unable to find a card to play
	if (gameState->selectedCard == nullptr)
	{
		GameState::updateState(gameState, GameState::StateType::Pass);
		return;
	}

	this->runAction(Sequence::create(
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::AIDecideTarget);
		}),
		nullptr
	));
}

void StateAIDecideCard::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateAIDecideCard::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
