#include "StateNeutral.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/HexusConfig.h"

using namespace cocos2d;

StateNeutral* StateNeutral::create()
{
	StateNeutral* instance = new StateNeutral();

	instance->autorelease();

	return instance;
}

StateNeutral::StateNeutral() : super(GameState::StateType::Neutral)
{
}

StateNeutral::~StateNeutral()
{
}

void StateNeutral::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateNeutral::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	this->activeGameState = gameState;

	if (gameState->playerHand->rowCards.size() == 0)
	{
		GameState::updateState(this->activeGameState, GameState::StateType::Pass);
		return;
	}

	this->initializeCallbacks(gameState);
	this->activeGameState->playerHand->enableRowCardInteraction();
}

void StateNeutral::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateNeutral::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
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

	this->activeGameState->selectedHandCard = card;
	this->activeGameState->selectedHandCard->stopAllActions();
	this->activeGameState->selectedHandCard->runAction(MoveTo::create(HexusConfig::cardSelectSpeed, this->activeGameState->selectedHandCard->position + Vec2(0.0f, HexusConfig::cardSelectOffsetY)));

	GameState::updateState(this->activeGameState, GameState::StateType::SelectionStaged);
}
