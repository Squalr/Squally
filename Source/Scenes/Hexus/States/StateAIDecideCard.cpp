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

	for (auto it = gameState->enemyHand->rowCards.begin(); it != gameState->enemyHand->rowCards.end(); it++)
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
			{
				// (Generally) Not useful if no enemy cards on field
				if (this->getEnemyCardsOnFieldCount(gameState) <= 0)
				{
					break;
				}

				// TODO: Capture overflow cases that might make this card useful against the player

				gameState->selectedCard = card;
				break;
			}
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
			case CardData::CardType::Special_OR:
			{
				// Ideally for OR the enemy would have 2 cards on the field
				if (this->getEnemyCardsOnFieldCount(gameState) < 2)
				{
					break;
				}

				// If the enemies weakest card == strongest, that means all enemy cards on the field have the same attack (thus OR is useless)
				// Also covers the case that the enemy only has cards with 0 attack
				if (this->getWeakestEnemyCardOnField(gameState) == this->getStrongestEnemyCardOnField(gameState))
				{
					break;
				}

				gameState->selectedCard = card;
				break;
			}
			case CardData::CardType::Special_ADD:
			{
				// No source cards available
				if (this->getEnemyCardsOnFieldCount(gameState) <= 0)
				{
					break;
				}

				// Happy case 1: There exists at least one combo to make the player overflow
				if (this->getStrongestEnemyCardOnField(gameState) + this->getStrongestPlayerCardOnField(gameState) > 15)
				{
					gameState->selectedCard = card;
					break;
				}

				// Happy case 2: There exists some combo to make a stronger enemy card
				if (this->getEnemyCardsOnFieldCount(gameState) >= 2)
				{
					std::vector<CardRow*> enemyRows = gameState->getEnemyRows();
					int lowest = 0;
					int otherLowest = 0;

					for (auto it = enemyRows.begin(); it != enemyRows.end(); it++)
					{
						for (auto cardIt = (*it)->rowCards.begin(); cardIt != (*it)->rowCards.end(); cardIt++)
						{
							int attack = (*cardIt)->getAttack();

							if (attack < lowest || attack < otherLowest)
							{
								lowest = std::min(lowest, otherLowest);
								otherLowest = attack;
							}
						}
					}

					if (lowest + otherLowest <= 15)
					{
						gameState->selectedCard = card;
						break;
					}
				}

				// Nothing reasonable found
				break;
			}
			case CardData::CardType::Special_MOV:
			{
				// Ideally for MOV there would be at least two cards on the field
				if ((this->getEnemyCardsOnFieldCount(gameState) +this->getPlayerCardsOnFieldCount(gameState)) >= 2)
				{
					break;
				}

				// Sad case: Freak scenario where all cards on the field have the same exact attack, rendering MOV useless
				if (this->getStrongestEnemyCardOnField(gameState) == this->getStrongestPlayerCardOnField(gameState) &&
					this->getStrongestEnemyCardOnField(gameState) == this->getWeakestEnemyCardOnField(gameState) &&
					this->getStrongestPlayerCardOnField(gameState) == this->getWeakestPlayerCardOnField(gameState))
				{
					break;
				}

				// Happy case 1: There exists some combo to make a weaker enemy card
				if (this->getEnemyCardsOnFieldCount(gameState) >= 1)
				{
					std::vector<CardRow*> enemyRows = gameState->getEnemyRows();
					int weakestPlayerCard = this->getWeakestPlayerCardOnField(gameState);
					bool solutionFound = false;

					for (auto it = enemyRows.begin(); it != enemyRows.end(); it++)
					{
						for (auto cardIt = (*it)->rowCards.begin(); cardIt != (*it)->rowCards.end(); cardIt++)
						{
							int attack = (*cardIt)->getAttack();

							if (attack > weakestPlayerCard)
							{
								solutionFound = true;
								break;
							}
						}
					}

					if (solutionFound)
					{
						gameState->selectedCard = card;

						break;
					}
				}

				// Happy case 2: There exists some combo to make a stronger player card
				if (this->getEnemyCardsOnFieldCount(gameState) >= 2 && this->getWeakestPlayerCardOnField(gameState) != this->getStrongestPlayerCardOnField(gameState))
				{
					gameState->selectedCard = card;
					break;
				}

				break;
			}
			case CardData::CardType::Special_AND:
			{
				// Ideally for AND the enemy would have 1 card and the player would have at least 1 card
				if (this->getEnemyCardsOnFieldCount(gameState) < 1 || this->getPlayerCardsOnFieldCount(gameState) < 1)
				{
					break;
				}

				// Sad case: Freak scenario where all cards on the field have the same exact attack, rendering AND useless
				if (this->getStrongestEnemyCardOnField(gameState) == this->getStrongestPlayerCardOnField(gameState) &&
					this->getStrongestEnemyCardOnField(gameState) == this->getWeakestEnemyCardOnField(gameState) &&
					this->getStrongestPlayerCardOnField(gameState) == this->getWeakestPlayerCardOnField(gameState))
				{
					break;
				}

				gameState->selectedCard = card;
				break;
			}
			case CardData::CardType::Special_XOR:
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

				// TODO: Determine in advance if the XOR will be useful. Some calculation required.

				gameState->selectedCard = card;
				break;
			}
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

				// Sad case 1: The strongest enemy card is 0
				if (this->getStrongestEnemyCardOnField(gameState) == 0)
				{
					break;
				}

				// Happy case 1: There exists at least one combo to make the enemy underflow
				// TODO: Prove that this ends up with a better card -- technically it might not
				if (this->getWeakestEnemyCardOnField(gameState) - this->getStrongestEnemyCardOnField(gameState) < 0)
				{
					gameState->selectedCard = card;
					break;
				}

				// Happy case 2: There exists some combo to make a weaker player card
				if (this->getPlayerCardsOnFieldCount(gameState) >= 1)
				{
					int result = this->getStrongestPlayerCardOnField(gameState) - this->getWeakestEnemyCardOnField(gameState);

					// The result is within the attack bounds -- subtraction succeeded without overflow
					if (result >= 0 && result < 15)
					{
						gameState->selectedCard = card;
						break;
					}
				}

				gameState->selectedCard = card;
				break;
			}
			default:
			{
				break;
			}
		}

		if (gameState->selectedCard != nullptr)
		{
			break;
		}
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
	int baseCardCount = 0;

	for (auto it = gameState->enemyHand->rowCards.begin(); it != gameState->enemyHand->rowCards.end(); it++)
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
	return gameState->playerHand->rowCards.size();
}

int StateAIDecideCard::getEnemyHandCount(GameState* gameState)
{
	return gameState->enemyHand->rowCards.size();
}

int StateAIDecideCard::getPlayerCardsOnFieldCount(GameState* gameState)
{
	std::vector<CardRow*> playerRows = gameState->getPlayerRows();
	int cardCount = 0;

	for (auto it = playerRows.begin(); it != playerRows.end(); it++)
	{
		cardCount += (*it)->rowCards.size();
	}

	return cardCount;
}

int StateAIDecideCard::getEnemyCardsOnFieldCount(GameState* gameState)
{
	std::vector<CardRow*> enemyRows = gameState->getEnemyRows();
	int cardCount = 0;

	for (auto it = enemyRows.begin(); it != enemyRows.end(); it++)
	{
		cardCount += (*it)->rowCards.size();
	}

	return cardCount;
}

unsigned int StateAIDecideCard::getStrongestEnemyCardOnField(GameState* gameState)
{
	std::vector<CardRow*> enemyRows = gameState->getEnemyRows();
	unsigned int strongest = 0;

	for (auto it = enemyRows.begin(); it != enemyRows.end(); it++)
	{
		for (auto cardIt = (*it)->rowCards.begin(); cardIt != (*it)->rowCards.end(); cardIt++)
		{
			strongest = std::max(strongest, (*cardIt)->getAttack());
		}
	}

	return strongest;
}

unsigned int StateAIDecideCard::getWeakestEnemyCardOnField(GameState* gameState)
{
	std::vector<CardRow*> enemyRows = gameState->getEnemyRows();
	unsigned int weakest = 0;

	for (auto it = enemyRows.begin(); it != enemyRows.end(); it++)
	{
		for (auto cardIt = (*it)->rowCards.begin(); cardIt != (*it)->rowCards.end(); cardIt++)
		{
			weakest = std::min(weakest, (*cardIt)->getAttack());
		}
	}

	return weakest;
}

unsigned int StateAIDecideCard::getStrongestPlayerCardOnField(GameState* gameState)
{
	std::vector<CardRow*> playerRows = gameState->getPlayerRows();
	unsigned int strongest = 0;

	for (auto it = playerRows.begin(); it != playerRows.end(); it++)
	{
		for (auto cardIt = (*it)->rowCards.begin(); cardIt != (*it)->rowCards.end(); cardIt++)
		{
			strongest = std::max(strongest, (*cardIt)->getAttack());
		}
	}

	return strongest;
}

unsigned int StateAIDecideCard::getWeakestPlayerCardOnField(GameState* gameState)
{
	std::vector<CardRow*> playerRows = gameState->getPlayerRows();
	unsigned int weakest = 0;

	for (auto it = playerRows.begin(); it != playerRows.end(); it++)
	{
		for (auto cardIt = (*it)->rowCards.begin(); cardIt != (*it)->rowCards.end(); cardIt++)
		{
			weakest = std::min(weakest, (*cardIt)->getAttack());
		}
	}

	return weakest;
}
