#include "StateAIDecideCardReplace.h"

#include <algorithm>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Utils/GameUtils.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Deck.h"

using namespace cocos2d;

StateAIDecideCardReplace* StateAIDecideCardReplace::create()
{
	StateAIDecideCardReplace* instance = new StateAIDecideCardReplace();

	instance->autorelease();

	return instance;
}

StateAIDecideCardReplace::StateAIDecideCardReplace() : super(GameState::StateType::AIDecideCardReplace)
{
	this->removedCards = std::vector<Card*>();
}

StateAIDecideCardReplace::~StateAIDecideCardReplace()
{
}

void StateAIDecideCardReplace::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);

	if (gameState->roundNumber == 0)
	{
		gameState->cardReplaceCount = std::min(Config::initialCardReplacements, gameState->enemyDeck->getCardCount());
	}
	else
	{
		gameState->cardReplaceCount = std::min(Config::midgameCardReplacements, gameState->enemyDeck->getCardCount());
	}
}

void StateAIDecideCardReplace::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	// AI card replace logic would go here, but we'll just leave it out. We'll just give the player an advantage here.

	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			GameState::updateState(gameState, GameState::StateType::CardReplace);
		}),
		nullptr
	));
}

void StateAIDecideCardReplace::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateAIDecideCardReplace::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}

void StateAIDecideCardReplace::replaceCard(Card* cardToReplace, GameState* gameState)
{
	if (gameState->cardReplaceCount > 0)
	{
		cardToReplace->disableInteraction();

		gameState->cardReplaceCount--;
		gameState->playerHand->removeCard(cardToReplace);

		this->removedCards.clear();
		this->removedCards.push_back(cardToReplace);

		// Remove all cards of the same type of the target card
		gameState->playerDeck->removeCardsWhere([=](Card* card)
		{
			if (card->cardData->getCardKey() == cardToReplace->cardData->getCardKey())
			{
				this->removedCards.push_back(card);
				return true;
			}

			return false;
		});

		// Insert removed cards at the bottom of the deck
		for (auto it = this->removedCards.begin(); it != this->removedCards.end(); it++)
		{
			gameState->playerDeck->insertCardBottom(*it, false, 0.5f);
		}

		// Get Our Replacement Card
		Card* replacement = gameState->playerDeck->drawCard();

		// Shouldn't happen -- error case
		if (replacement == nullptr)
		{
			return;
		}

		GameUtils::changeParent(replacement, this, true);
		replacement->reveal();

		// Update the state and either re-enter this state or exit to coinflip
		if (gameState->cardReplaceCount <= 0)
		{
			gameState->playerHand->disableRowCardInteraction();
			gameState->enemyHand->insertCard(replacement, 0.0f);
		}
		else
		{
			gameState->enemyHand->insertCard(replacement, 0.0f);
			GameState::updateState(gameState, GameState::StateType::AIDecideCardReplace);
		}
	}
}
