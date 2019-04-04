#include "HexusAIHelper.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

std::tuple<CardRow*, int> HexusAIHelper::getBestRow(Card* candidateCardToPlay, GameState* gameState)
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

		int diff = row->simulateCardEffect(candidateCardToPlay) * (row->isPlayerRow() ? -1 : 1);

		if (diff >= bestDiff)
		{
			bestDiff = diff;
			bestRow = row;
		}
	}

	return std::tuple<CardRow*, int>(bestRow, bestDiff);
}

std::tuple<Card*, Card*, int> HexusAIHelper::getBestSourceAndTarget(Card* candidateCardToPlay, GameState* gameState)
{
	std::vector<Card*> enemyCards = gameState->getEnemyCards();
	std::vector<CardRow*> cardRows = gameState->getAllRows();
	int bestDiff = std::numeric_limits<int>::min();
	Card* bestSource = nullptr;
	Card* bestTarget = nullptr;

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
					candidateCardToPlay->cardData->cardType,
					sourceCard->getAttack()
				);

				int before = destinationCard->getAttack();
				int after = destinationCard->simulateOperation(operation);
				int diff = (after - before) * (targetRow->isPlayerRow() ? -1 : 1);

				if (diff > bestDiff)
				{
					bestDiff = diff;
					bestSource = sourceCard;
					bestTarget = destinationCard;
				}
			}
		}
	}

	return std::tuple<Card*, Card*, int>(bestSource, bestTarget, bestDiff);
}

std::tuple<Card*, int> HexusAIHelper::getBestOperationTarget(Card* operationCard, GameState* gameState)
{
	std::vector<CardRow*> cardRows = gameState->getAllRows();
	int bestDiff = std::numeric_limits<int>::min();
	Card* bestCard = nullptr;

	for (auto it = cardRows.begin(); it != cardRows.end(); it++)
	{
		CardRow* targetRow = *it;

		for (auto targetCardIterator = targetRow->rowCards.begin(); targetCardIterator != targetRow->rowCards.end(); targetCardIterator++)
		{
			Card* destinationCard = *targetCardIterator;

			Card::Operation operation = Card::toOperation(
				operationCard->cardData->cardType,
				destinationCard->getAttack()
			);

			int before = destinationCard->getAttack();
			int after = destinationCard->simulateOperation(operation);
			int diff = (after - before) * (targetRow->isPlayerRow() ? -1 : 1);

			if (diff > bestDiff)
			{
				bestDiff = diff;
				bestCard = destinationCard;
			}
		}
	}

	return std::tuple<Card*, int>(bestCard, bestDiff);
}

std::tuple<Card*, int> HexusAIHelper::getStrongestPlayerCard(GameState* gameState)
{
	std::vector<CardRow*> playerRows = gameState->getPlayerRows();
	int bestDiff = std::numeric_limits<int>::min();
	Card* bestCard = nullptr;

	for (auto it = playerRows.begin(); it != playerRows.end(); it++)
	{
		CardRow* targetRow = *it;

		for (auto targetCardIterator = targetRow->rowCards.begin(); targetCardIterator != targetRow->rowCards.end(); targetCardIterator++)
		{
			Card* destinationCard = *targetCardIterator;

			int diff = destinationCard->getAttack();

			if (diff > bestDiff)
			{
				bestDiff = diff;
				bestCard = destinationCard;
			}
		}
	}

	return std::tuple<Card*, int>(bestCard, bestDiff);
}

std::tuple<Card*, int> HexusAIHelper::getStrongestAugmentedPlayerCard(GameState* gameState)
{
	std::vector<CardRow*> playerRows = gameState->getPlayerRows();
	int bestDiff = std::numeric_limits<int>::min();
	Card* bestCard = nullptr;

	for (auto it = playerRows.begin(); it != playerRows.end(); it++)
	{
		CardRow* targetRow = *it;

		for (auto targetCardIterator = targetRow->rowCards.begin(); targetCardIterator != targetRow->rowCards.end(); targetCardIterator++)
		{
			Card* destinationCard = *targetCardIterator;

			int diff = destinationCard->getAttack();

			if (destinationCard->getAttack() > destinationCard->getOriginalAttack() && diff > bestDiff)
			{
				bestDiff = diff;
				bestCard = destinationCard;
			}
		}
	}

	return std::tuple<Card*, int>(bestCard, bestDiff);
}
