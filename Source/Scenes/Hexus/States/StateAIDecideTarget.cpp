#include "StateAIDecideTarget.h"

StateAIDecideTarget* StateAIDecideTarget::create()
{
	StateAIDecideTarget* instance = new StateAIDecideTarget();

	instance->autorelease();

	return instance;
}

StateAIDecideTarget::StateAIDecideTarget() : StateBase(GameState::StateType::AIDecideTarget)
{
}

StateAIDecideTarget::~StateAIDecideTarget()
{
}

void StateAIDecideTarget::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateAIDecideTarget::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	// Unable to find a card to play (ie it would be disadvantageous to play any card for the opponent)
	if (gameState->selectedHandCard == nullptr)
	{
		this->runAction(Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([=]()
			{
				GameState::updateState(gameState, GameState::StateType::Pass);
			}),
			nullptr
		));

		return;
	}

	switch (gameState->selectedHandCard->cardData->cardType)
	{
		case CardData::CardType::Binary:
		{
			gameState->selectedRow = gameState->enemyBinaryCards;
			break;
		}
		case CardData::CardType::Decimal:
		{
			gameState->selectedRow = gameState->enemyDecimalCards;
			break;
		}
		case CardData::CardType::Hexidecimal:
		{
			gameState->selectedRow = gameState->enemyHexCards;
			break;
		}
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		{
			// Calculate the best row to apply the card to
			CardRow* bestRow = nullptr;
			std::vector<CardRow*> rows = gameState->getAllRows();

			int bestDiff = std::numeric_limits<int>::min();

			for (auto it = rows.begin(); it != rows.end(); it++)
			{
				CardRow* row = *it;

				if (row->isEmpty())
				{
					continue;
				}

				int diff = row->simulateCardEffect(gameState->selectedHandCard) * (row->isPlayerRow() ? -1 : 1);

				if (diff >= bestDiff)
				{
					bestDiff = diff;
					bestRow = row;
				}
			}

			if (bestDiff > 0)
			{
				gameState->stagedCombineCardRow = bestRow;
			}

			gameState->selectedRow = gameState->stagedCombineCardRow;
			break;
		}
		case CardData::CardType::Special_MOV:
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
		{
			std::vector<Card*> enemyCards = gameState->getEnemyCards();
			std::vector<CardRow*> cardRows = gameState->getAllRows();
			int bestDiff = std::numeric_limits<int>::min();

			// Simulate running the card on all rows
			for (auto it = cardRows.begin(); it != cardRows.end(); it++)
			{
				CardRow* targetRow = *it;

				for (auto sourceCardIterator = enemyCards.begin(); sourceCardIterator != enemyCards.end(); sourceCardIterator++)
				{
					Card* sourceCard = *sourceCardIterator;

					for (auto targetCardIterator = targetRow->rowCards.begin(); targetCardIterator != targetRow->rowCards.end(); targetCardIterator++)
					{
						Card* destinationCard = *targetCardIterator;

						if (sourceCard == destinationCard)
						{
							// We're not allowed to apply a card to itself
							continue;
						}

						Card::Operation operation = Card::toOperation(
							gameState->selectedHandCard->cardData->cardType,
							sourceCard->getAttack()
						);

						int before = destinationCard->getAttack();
						int after = destinationCard->simulateOperation(operation);
						int diff = (after - before) * (targetRow->isPlayerRow() ? -1 : 1);

						if (diff > bestDiff)
						{
							bestDiff = diff;

							// Save the best so far
							gameState->selectedSourceCard = sourceCard;
							gameState->selectedDestinationCard = destinationCard;
						}
					}
				}
			}

			break;
		}
		case CardData::CardType::Special_INV:
		{
			std::vector<CardRow*> cardRows = gameState->getAllRows();
			int bestDiff = std::numeric_limits<int>::min();

			for (auto it = cardRows.begin(); it != cardRows.end(); it++)
			{
				CardRow* targetRow = *it;

				for (auto targetCardIterator = targetRow->rowCards.begin(); targetCardIterator != targetRow->rowCards.end(); targetCardIterator++)
				{
					Card* destinationCard = *targetCardIterator;

					Card::Operation operation = Card::toOperation(
						gameState->selectedHandCard->cardData->cardType,
						destinationCard->getAttack()
					);

					int before = destinationCard->getAttack();
					int after = destinationCard->simulateOperation(operation);
					int diff = (after - before) * (targetRow->isPlayerRow() ? -1 : 1);

					if (diff > bestDiff)
					{
						bestDiff = diff;

						// Save the best so far
						gameState->selectedDestinationCard = destinationCard;
					}
				}
			}

			break;
		}
		default:
		{
			break;
		}
	}

	this->runAction(Sequence::create(
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::PlayCard);
		}),
		nullptr
	));
}

void StateAIDecideTarget::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateAIDecideTarget::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
