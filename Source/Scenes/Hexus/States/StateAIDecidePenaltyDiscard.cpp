#include "StateAIDecidePenaltyDiscard.h"

StateAIDecidePenaltyDiscard* StateAIDecidePenaltyDiscard::create()
{
	StateAIDecidePenaltyDiscard* instance = new StateAIDecidePenaltyDiscard();

	instance->autorelease();

	return instance;
}

StateAIDecidePenaltyDiscard::StateAIDecidePenaltyDiscard() : StateBase(GameState::StateType::AIDecidePenaltyDiscard)
{
}

StateAIDecidePenaltyDiscard::~StateAIDecidePenaltyDiscard()
{
}

void StateAIDecidePenaltyDiscard::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateAIDecidePenaltyDiscard::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	while (gameState->playerLastStanded && gameState->penaltyCardsPlayed > 0 && gameState->enemyHand->getCardCount() > 0)
	{
		Card* weakestCard = gameState->enemyHand->rowCards[0];

		for (auto it = gameState->enemyHand->rowCards.begin(); it != gameState->enemyHand->rowCards.end(); it++)
		{
			switch ((*it)->cardData->cardType)
			{
				case CardData::Binary:
				case CardData::Decimal:
				case CardData::Hexidecimal:
				{
					if (weakestCard->cardData->isSpecialCard() || (*it)->getAttack() < weakestCard->getAttack())
					{
						weakestCard = (*it);
					}

					break;
				}
				default:
					break;
			}
		}

		gameState->enemyHand->removeCard(weakestCard);
		gameState->enemyDeck->insertCardTop(weakestCard, true, Config::cardDrawDelay);

		gameState->penaltyCardsPlayed--;
	}

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::PenaltyDiscard);
		}),
		nullptr
	));
}

void StateAIDecidePenaltyDiscard::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateAIDecidePenaltyDiscard::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
