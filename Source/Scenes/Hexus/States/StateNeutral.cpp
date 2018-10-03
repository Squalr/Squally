#include "StateNeutral.h"

StateNeutral* StateNeutral::create()
{
	StateNeutral* instance = new StateNeutral();

	instance->autorelease();

	return instance;
}

StateNeutral::StateNeutral() : StateBase(GameState::StateType::Neutral)
{
}

StateNeutral::~StateNeutral()
{
}

void StateNeutral::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateNeutral::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	this->activeGameState = gameState;

	if (gameState->playerHand->rowCards->size() == 0)
	{
		GameState::updateState(this->activeGameState, GameState::StateType::Pass);
		return;
	}

	this->initializeCallbacks(gameState);
	this->activeGameState->playerHand->enableRowCardInteraction();
}

void StateNeutral::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateNeutral::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}

void StateNeutral::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateNeutral::selectCard, this));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(StateNeutral::selectCard, this));
}

void StateNeutral::selectCard(Card* card)
{
	if (card == nullptr)
	{
		return;
	}

	this->activeGameState->selectedCard = card;
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

	GameState::updateState(this->activeGameState, GameState::StateType::SelectionStaged);
}
