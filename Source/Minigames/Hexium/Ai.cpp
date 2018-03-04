#include "Ai.h"

void Ai::performAiActions(GameState* gameState)
{
	bool done = false;

	for (auto it = gameState->enemyHand->rowCards->begin(); it != gameState->enemyHand->rowCards->end(); it++)
	{
		Card* card = *it;

		switch (card->cardData->cardType)
		{
		case CardData::CardType::Binary:
			gameState->enemyHand->removeCard(card);
			gameState->enemyBinaryCards->insertCard(card, Config::insertDelay);
			done = true;
			break;
		case CardData::CardType::Decimal:
			gameState->enemyHand->removeCard(card);
			gameState->enemyDecimalCards->insertCard(card, Config::insertDelay);
			done = true;
			break;
		case CardData::CardType::Hexidecimal:
			gameState->enemyHand->removeCard(card);
			gameState->enemyHexCards->insertCard(card, Config::insertDelay);
			done = true;
			break;
		}

		if (done)
		{
			break;
		}
	}

	gameState->endTurn();
}
