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
	if (gameState->selectedCard == nullptr)
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

	switch (gameState->selectedCard->cardData->cardType)
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
		case CardData::CardType::Special_INV:
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

				int diff = row->simulateCardEffect(gameState->selectedCard) * (row->isPlayerRow() ? -1 : 1);

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
			// n^2 card compare to figure out the best strategy
			// Maybe there is some better way to do this calculation

			std::vector<Card*> cards = gameState->getEnemyCards(); // all valid source cards for the operation must be our own
			Card* bestSourceCard = nullptr;
			Card* bestTargetCard = nullptr;
			int bestDiff = std::numeric_limits<int>::min();

			// First simulate buffing your own cards
			for (auto sourceCardIterator = cards.begin(); sourceCardIterator != cards.end(); sourceCardIterator++)
			{
				Card* sourceCard = *sourceCardIterator;

				// First we iterate through only our own cards
				for (auto targetCardIterator = cards.begin(); targetCardIterator != cards.end(); targetCardIterator++)
				{
					Card* targetCard = *targetCardIterator;
					if (sourceCard == targetCard) {
						continue; // we're not allowed to apply a card to itself
					}

					Card::Operation operation = Card::toOperation(
						gameState->selectedCard->cardData->cardType,
						sourceCard->getAttack()
					);

					int before = targetCard->getAttack();
					int after = targetCard->simulateOperation(operation);
					int diff = (after - before);

					if (diff > bestDiff) {
						bestDiff = diff;
						bestSourceCard = sourceCard;
						bestTargetCard = targetCard;
					}
				}
			}

			// Then simulate attacking the player
			std::vector<Card*> playerCards = gameState->getPlayerCards();
			for (auto sourceCardIterator = cards.begin(); sourceCardIterator != cards.end(); sourceCardIterator++)
			{
				Card* sourceCard = *sourceCardIterator;

				// This time we iterate through the players cards
				for (auto targetCardIterator = playerCards.begin(); targetCardIterator != playerCards.end(); targetCardIterator++)
				{
					Card* targetCard = *targetCardIterator;

					if (sourceCard == targetCard) {
						continue; // we're not allowed to apply a card to itself
					}

					Card::Operation operation = Card::toOperation(
						gameState->selectedCard->cardData->cardType,
						sourceCard->getAttack()
					);

					// multiply by negative 1 to flip the diff because we want to hurt the player
					int before = targetCard->getAttack();
					int after = targetCard->simulateOperation(operation);
					int diff = (after - before) * -1;

					if (diff > bestDiff)
					{
						bestDiff = diff;
						bestSourceCard = sourceCard;
						bestTargetCard = targetCard;
					}
				}
			}

			gameState->stagedCombineSourceCard = bestSourceCard;
			gameState->stagedCombineTargetCard = bestTargetCard;

			break;
		}
		default:
			break;
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
