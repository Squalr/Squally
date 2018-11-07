#include "StateSelectionStaged.h"

StateSelectionStaged* StateSelectionStaged::create()
{
	StateSelectionStaged* instance = new StateSelectionStaged();

	instance->autorelease();

	return instance;
}

StateSelectionStaged::StateSelectionStaged() : StateBase(GameState::StateType::SelectionStaged)
{
}

StateSelectionStaged::~StateSelectionStaged()
{
}

void StateSelectionStaged::initializePositions()
{
	StateBase::initializePositions();
}

void StateSelectionStaged::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateSelectionStaged::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	gameState->playerHand->enableRowCardInteraction();

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
			this->initializeSelectablesAndCallbacks(gameState);
			break;
		default:
			break;
	}
}

void StateSelectionStaged::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
			this->initializeSelectablesAndCallbacks(gameState);
			break;
		case GameState::Turn::Enemy:
			break;
		default:
			break;
	}
}

void StateSelectionStaged::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}

void StateSelectionStaged::initializeSelectablesAndCallbacks(GameState* gameState)
{
	gameState->playerHand->enableRowCardInteraction();
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateSelectionStaged::selectCard, this, gameState));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(StateSelectionStaged::selectCard, this, gameState));

	switch (gameState->selectedCard->cardData->cardType)
	{
		case CardData::CardType::Binary:
			gameState->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			break;
		case CardData::CardType::Decimal:
			gameState->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			break;
		case CardData::CardType::Hexidecimal:
			gameState->playerHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			break;
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		case CardData::CardType::Special_INV:
			gameState->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			gameState->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			gameState->playerHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			gameState->enemyBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			gameState->enemyDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			gameState->enemyHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::onRowChosen, this, gameState));
			break;
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
			gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this, gameState));
			gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this, gameState));
			gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this, gameState));
			break;
		default:
			break;
	}
}

void StateSelectionStaged::selectCard(Card* card, GameState* gameState)
{
	if (card == nullptr || gameState->selectedCard == nullptr)
	{
		return;
	}

	// Unstage/deselect card if clicking the active card
	if (card == gameState->selectedCard)
	{
		gameState->selectedCard->stopAllActions();
		gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position));
		GameState::updateState(gameState, GameState::StateType::Neutral);
		gameState->selectedCard = nullptr;
	}
	else
	{
		// Otherwise this is just a selection/re-staging of a new card
		gameState->selectedCard->stopAllActions();
		gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position));

		gameState->selectedCard = card;
		gameState->selectedCard->stopAllActions();
		gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

		// Transition to the same state (re-initialize things)
		GameState::updateState(gameState, GameState::StateType::SelectionStaged);
	}
}

void StateSelectionStaged::stageSelectedCombineCard(Card* card, GameState* gameState)
{
	if (gameState->selectedCard == nullptr)
	{
		return;
	}

	gameState->stagedCombineSourceCard = card;
	GameState::updateState(gameState, GameState::StateType::CombineStaged);
}

void StateSelectionStaged::onRowChosen(CardRow* cardRow, GameState* gameState)
{
	gameState->selectedRow = cardRow;

	GameState::updateState(gameState, GameState::StateType::PlayCard);
}
