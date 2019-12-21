#include "StateSourceCardStaged.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"

using namespace cocos2d;

StateSourceCardStaged* StateSourceCardStaged::create()
{
	StateSourceCardStaged* instance = new StateSourceCardStaged();

	instance->autorelease();

	return instance;
}

StateSourceCardStaged::StateSourceCardStaged() : super(GameState::StateType::CombineStaged)
{
}

StateSourceCardStaged::~StateSourceCardStaged()
{
}

void StateSourceCardStaged::initializePositions()
{
	super::initializePositions();
}

void StateSourceCardStaged::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateSourceCardStaged::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
		{
			if (gameState->selectedHandCard != nullptr)
			{
				gameState->selectedHandCard->focus();

				switch (gameState->selectedHandCard->cardData->getCardType())
				{
					case CardData::CardType::Special_MOV:
					case CardData::CardType::Special_AND:
					case CardData::CardType::Special_OR:
					case CardData::CardType::Special_XOR:
					case CardData::CardType::Special_ADD:
					case CardData::CardType::Special_SUB:
					{
						std::vector<Card*> ignoreList = std::vector<Card*>
						{
							gameState->selectedHandCard,
							gameState->selectedSourceCard,
						};

						gameState->selectedSourceCard->cardEffects->runEffect(CardEffects::CardEffect::FocusRing);

						gameState->enemyBinaryCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
						gameState->enemyDecimalCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
						gameState->enemyHexCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
						gameState->playerBinaryCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
						gameState->playerDecimalCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
						gameState->playerHexCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);

						break;
					}
					default:
					{
						break;
					}
				}
			}

			this->initializeCallbacks(gameState);
			break;
		}
		default:
		{
			break;
		}
	}
}

void StateSourceCardStaged::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateSourceCardStaged::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);

	gameState->playerHand->clearEffects();
	gameState->enemyHand->clearEffects();
	gameState->playerBinaryCards->clearEffects();
	gameState->playerDecimalCards->clearEffects();
	gameState->playerHexCards->clearEffects();
	gameState->enemyBinaryCards->clearEffects();
	gameState->enemyDecimalCards->clearEffects();
	gameState->enemyHexCards->clearEffects();
}

void StateSourceCardStaged::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateSourceCardStaged::selectCard, this, gameState));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(StateSourceCardStaged::selectCard, this, gameState));

	gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateSourceCardStaged::stageCombineTarget, this, gameState));
	gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateSourceCardStaged::stageCombineTarget, this, gameState));
	gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(StateSourceCardStaged::stageCombineTarget, this, gameState));
	gameState->enemyBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateSourceCardStaged::stageCombineTarget, this, gameState));
	gameState->enemyDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateSourceCardStaged::stageCombineTarget, this, gameState));
	gameState->enemyHexCards->enableRowCardSelection(CC_CALLBACK_1(StateSourceCardStaged::stageCombineTarget, this, gameState));
}

void StateSourceCardStaged::selectCard(Card* card, GameState* gameState)
{
	if (card == nullptr || gameState->selectedHandCard == nullptr)
	{
		return;
	}

	// Unstage/deselect card if clicking the active card
	if (card == gameState->selectedHandCard)
	{
		gameState->selectedSourceCard = nullptr;
		gameState->selectedHandCard->stopAllActions();
		gameState->selectedHandCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedHandCard->position));
		gameState->selectedHandCard = nullptr;

		GameState::updateState(gameState, GameState::StateType::Neutral);
		return;
	}

	// Otherwise this is just a selection/re-staging of a new card
	gameState->selectedHandCard->stopAllActions();
	gameState->selectedHandCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedHandCard->position));

	gameState->selectedHandCard = card;
	gameState->selectedHandCard->stopAllActions();
	gameState->selectedHandCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedHandCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

	// Transition to the selection state (re-initialize things)
	GameState::updateState(gameState, GameState::StateType::SelectionStaged);
}

void StateSourceCardStaged::stageCombineTarget(Card* card, GameState* gameState)
{
	// If we click a card that is already selected our source, deselect our source
	if (gameState->selectedSourceCard == card)
	{
		gameState->selectedSourceCard = nullptr;

		// Transition to the selection state (re-initialize things)
		GameState::updateState(gameState, GameState::StateType::SelectionStaged);
		return;
	}

	// we assign the source card first, then the destination/target
	if (gameState->selectedSourceCard == nullptr)
	{
		gameState->selectedSourceCard = card;
	}
	else
	{
		gameState->selectedDestinationCard = card;
	}

	switch (gameState->selectedHandCard->cardData->getCardType())
	{
		case CardData::CardType::Special_MOV:
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
		{
			if (gameState->selectedSourceCard != nullptr && gameState->selectedDestinationCard != nullptr)
			{
				GameState::updateState(gameState, GameState::StateType::PlayCard);
			}
			break;
		}
		default:
		{
			break;
		}
	}
}
