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

	for (auto it = gameState->enemyHand->rowCards->begin(); it != gameState->enemyHand->rowCards->end(); it++)
	{
		Card* card = *it;

		switch (card->cardData->cardType)
		{
			case CardData::CardType::Binary:
			case CardData::CardType::Decimal:
			case CardData::CardType::Hexidecimal:
			{
				gameState->selectedCard = card;
				break;
			}
			case CardData::CardType::Special_SHR:
			{
				// Not useful if no player cards on field
				if (this->getPlayerCardsOnFieldCount(gameState) <= 0)
				{
					break;
				}

				gameState->selectedCard = card;
				break;
			}
			case CardData::CardType::Special_SHL:
				// (Generally) Not useful if no enemy cards on field
				if (this->getEnemyCardsOnFieldCount(gameState) <= 0)
				{
					break;
				}

				gameState->selectedCard = card;
				break;
			case CardData::CardType::Special_FLIP1:
			case CardData::CardType::Special_FLIP2:
			case CardData::CardType::Special_FLIP3:
			case CardData::CardType::Special_FLIP4:
			case CardData::CardType::Special_INV:
			{
				// Not useful if no cards on field
				if (this->getEnemyCardsOnFieldCount(gameState) <= 0 && this->getPlayerCardsOnFieldCount(gameState) <= 0)
				{
					break;
				}

				gameState->selectedCard = card;
				break;
			}
			case CardData::CardType::Special_AND:
			case CardData::CardType::Special_OR:
			case CardData::CardType::Special_XOR:
			case CardData::CardType::Special_ADD:
			case CardData::CardType::Special_SUB:
			{
				// No source cards available
				if (this->getEnemyCardsOnFieldCount(gameState) <= 0)
				{
					break;
				}

				// No targets available
				if (this->getEnemyCardsOnFieldCount(gameState) + this->getPlayerCardsOnFieldCount(gameState) <= 1)
				{
					break;
				}

				gameState->selectedCard = card;
				break;
			}
			default:
				break;
		}

		if (gameState->selectedCard != nullptr)
		{
			break;
		}
	}

	// Could not find a card to play (disadvantageous to do so)
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

int StateAIDecideCard::getBaseCardsInHandCount(GameState* gameState)
{
	std::vector<Card*>* handCards = gameState->enemyHand->rowCards;
	int baseCardCount = 0;

	for (auto it = handCards->begin(); it != handCards->end(); it++)
	{
		Card* card = *it;

		switch (card->cardData->cardType)
		{
			case CardData::CardType::Binary:
			case CardData::CardType::Decimal:
			case CardData::CardType::Hexidecimal:
				baseCardCount++;
				break;
			default:
				break;
		}
	}

	return baseCardCount;
}

int StateAIDecideCard::getPlayerHandCount(GameState* gameState)
{
	return gameState->playerHand->rowCards->size();
}

int StateAIDecideCard::getEnemyHandCount(GameState* gameState)
{
	return gameState->enemyHand->rowCards->size();
}

int StateAIDecideCard::getPlayerCardsOnFieldCount(GameState* gameState)
{
	std::vector<CardRow*> playerRows = gameState->getPlayerRows();
	int cardCount = 0;

	for (auto it = playerRows.begin(); it != playerRows.end(); it++)
	{
		cardCount += (*it)->rowCards->size();
	}

	return cardCount;
}

int StateAIDecideCard::getEnemyCardsOnFieldCount(GameState* gameState)
{
	std::vector<CardRow*> enemyRows = gameState->getPlayerRows();
	int cardCount = 0;

	for (auto it = enemyRows.begin(); it != enemyRows.end(); it++)
	{
		cardCount += (*it)->rowCards->size();
	}

	return cardCount;
}
