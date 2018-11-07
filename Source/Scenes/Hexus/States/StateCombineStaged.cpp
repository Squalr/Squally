#include "StateCombineStaged.h"

StateCombineStaged* StateCombineStaged::create()
{
	StateCombineStaged* instance = new StateCombineStaged();

	instance->autorelease();

	return instance;
}

StateCombineStaged::StateCombineStaged() : StateBase(GameState::StateType::CombineStaged)
{
}

StateCombineStaged::~StateCombineStaged()
{
}

void StateCombineStaged::initializePositions()
{
	StateBase::initializePositions();
}

void StateCombineStaged::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateCombineStaged::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	gameState = gameState;

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
		{
			this->initializeCallbacks(gameState);
			break;
		}
		default:
			break;
	}
}

void StateCombineStaged::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateCombineStaged::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}

void StateCombineStaged::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateCombineStaged::selectCard, this, gameState));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(StateCombineStaged::selectCard, this, gameState));

	gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
	gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
	gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
	gameState->enemyBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
	gameState->enemyDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
	gameState->enemyHexCards->enableRowCardSelection(CC_CALLBACK_1(StateCombineStaged::stageCombineTarget, this, gameState));
}

void StateCombineStaged::selectCard(Card* card, GameState* gameState)
{
	if (card == nullptr || gameState->selectedCard == nullptr)
	{
		return;
	}

	// Unstage/deselect card if clicking the active card
	if (card == gameState->selectedCard)
	{
		gameState->stagedCombineSourceCard = nullptr;
		gameState->selectedCard->stopAllActions();
		gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position));
		gameState->selectedCard = nullptr;

		GameState::updateState(gameState, GameState::StateType::Neutral);
		return;
	}

	// Otherwise this is just a selection/re-staging of a new card
	gameState->selectedCard->stopAllActions();
	gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position));

	gameState->selectedCard = card;
	gameState->selectedCard->stopAllActions();
	gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

	// Transition to the selection state (re-initialize things)
	GameState::updateState(gameState, GameState::StateType::SelectionStaged);
}


void StateCombineStaged::stageCombineTarget(Card* card, GameState* gameState)
{
	// If we click a card that is already selected our source, deselect our source
	if (gameState->stagedCombineSourceCard == card)
	{
		card->unfocus();
		gameState->stagedCombineSourceCard = nullptr;
		return;
	}

	// If we click a card that is already selected our destination, deselect our destination
	if (gameState->stagedCombineTargetCard == card)
	{
		card->unfocus();
		gameState->stagedCombineTargetCard = nullptr;
		return;
	}

	// we assign the source card first, then the destination/target
	if (gameState->stagedCombineSourceCard == nullptr)
	{
		card->focus();
		gameState->stagedCombineSourceCard = card;
	}
	else
	{
		card->focus();
		gameState->stagedCombineTargetCard = card;
	}

	switch (gameState->selectedCard->cardData->cardType)
	{
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
		{
			if (gameState->stagedCombineSourceCard != nullptr && gameState->stagedCombineTargetCard != nullptr)
			{
				gameState->stagedCombineSourceCard->unfocus();

				GameState::updateState(gameState, GameState::StateType::PlayCard);
			}
			break;
		}
		default:
			break;
	}
}
