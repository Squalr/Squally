#include "StateSelectionStaged.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/CardRow.h"

using namespace cocos2d;

StateSelectionStaged* StateSelectionStaged::create()
{
	StateSelectionStaged* instance = new StateSelectionStaged();

	instance->autorelease();

	return instance;
}

StateSelectionStaged::StateSelectionStaged() : super(GameState::StateType::SelectionStaged)
{
}

StateSelectionStaged::~StateSelectionStaged()
{
}

void StateSelectionStaged::initializePositions()
{
	super::initializePositions();
}

void StateSelectionStaged::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateSelectionStaged::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	gameState->playerHand->enableRowCardInteraction();

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
		{
			this->initializeSelectablesAndCallbacks(gameState);
			break;
		}
		default:
		{
			break;
		}
	}
}

void StateSelectionStaged::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
		{
			this->initializeSelectablesAndCallbacks(gameState);
			break;
		}
		case GameState::Turn::Enemy:
		{
			break;
		}
		default:
		{
			break;
		}
	}
}

void StateSelectionStaged::onStateExit(GameState* gameState)
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

void StateSelectionStaged::initializeSelectablesAndCallbacks(GameState* gameState)
{
	gameState->playerHand->enableRowCardInteraction();
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateSelectionStaged::selectCard, this, gameState));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(StateSelectionStaged::selectCard, this, gameState));

	switch (gameState->selectedHandCard->cardData->cardType)
	{
		case CardData::CardType::Binary:
		{
			gameState->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			break;
		}
		case CardData::CardType::Decimal:
		{
			gameState->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			break;
		}
		case CardData::CardType::Hexidecimal:
		{
			gameState->playerHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			break;
		}
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		{
			gameState->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			gameState->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			gameState->playerHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			gameState->enemyBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			gameState->enemyDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			gameState->enemyHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			break;
		}
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

			gameState->playerBinaryCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
			gameState->playerDecimalCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
			gameState->playerHexCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);

			gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this, gameState));
			gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this, gameState));
			gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this, gameState));
			break;
		}
		case CardData::CardType::Special_INV:
		{
			std::vector<Card*> ignoreList = std::vector<Card*>
			{
				gameState->selectedHandCard,
				gameState->selectedSourceCard,
			};

			gameState->playerBinaryCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
			gameState->playerDecimalCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
			gameState->playerHexCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
			gameState->enemyBinaryCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
			gameState->enemyDecimalCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);
			gameState->enemyHexCards->runEffect(CardEffects::CardEffect::SelectionPulse, ignoreList);

			gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::immediatelyPlayCard, this, gameState));
			gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::immediatelyPlayCard, this, gameState));
			gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::immediatelyPlayCard, this, gameState));
			gameState->enemyBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::immediatelyPlayCard, this, gameState));
			gameState->enemyDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::immediatelyPlayCard, this, gameState));
			gameState->enemyHexCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::immediatelyPlayCard, this, gameState));
			break;
		}
		default:
		{
			break;
		}
	}
}

void StateSelectionStaged::selectCard(Card* card, GameState* gameState)
{
	if (card == nullptr || gameState->selectedHandCard == nullptr)
	{
		return;
	}

	// Unstage/deselect card if clicking the active card
	if (card == gameState->selectedHandCard)
	{
		gameState->selectedHandCard->stopAllActions();
		gameState->selectedHandCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedHandCard->position));
		GameState::updateState(gameState, GameState::StateType::Neutral);
		gameState->selectedHandCard = nullptr;
	}
	else
	{
		// Otherwise this is just a selection/re-staging of a new card
		gameState->selectedHandCard->stopAllActions();
		gameState->selectedHandCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedHandCard->position));

		gameState->selectedHandCard = card;
		gameState->selectedHandCard->stopAllActions();
		gameState->selectedHandCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedHandCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

		// Transition to the same state (re-initialize things)
		GameState::updateState(gameState, GameState::StateType::SelectionStaged);
	}
}

void StateSelectionStaged::stageSelectedCombineCard(Card* card, GameState* gameState)
{
	if (gameState->selectedHandCard == nullptr)
	{
		return;
	}

	gameState->selectedSourceCard = card;
	GameState::updateState(gameState, GameState::StateType::CombineStaged);
}

void StateSelectionStaged::immediatelyPlayCard(Card* card, GameState* gameState)
{
	if (gameState->selectedHandCard == nullptr)
	{
		return;
	}

	gameState->selectedDestinationCard = card;
	GameState::updateState(gameState, GameState::StateType::PlayCard);
}

void StateSelectionStaged::onRowChosen(CardRow* cardRow, GameState* gameState)
{
	gameState->selectedRow = cardRow;

	GameState::updateState(gameState, GameState::StateType::PlayCard);
}
