#include "ControlReplaceCards.h"

ControlReplaceCards* ControlReplaceCards::create()
{
	ControlReplaceCards* instance = new ControlReplaceCards();

	instance->autorelease();

	return instance;
}

ControlReplaceCards::ControlReplaceCards()
{
	this->replacedCards = new std::set<Card*>();
}

ControlReplaceCards::~ControlReplaceCards()
{
	delete(this->replacedCards);
}

void ControlReplaceCards::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void ControlReplaceCards::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	switch (gameState->stateType)
	{
		case GameState::StateType::ControlReplaceCards:
			// State just entered -- perform initialization and re-enter this state to allow other components to have up-to-date info
			if (gameState->stateType != gameState->previousStateType)
			{
				this->initializeCardReplace(gameState);
				GameState::updateState(gameState, GameState::StateType::ControlReplaceCards);
				return;
			}

			this->initializeCallbacks(gameState);
			break;
		default:
			if (gameState->previousStateType == GameState::StateType::ControlReplaceCards)
			{
				// Restore hand to proper position
				Size visibleSize = Director::getInstance()->getVisibleSize();
				GameUtils::changeParent(gameState->playerHand, gameState, true);
				gameState->playerHand->setCardScale(Card::cardScale, 0.25f);
				gameState->playerHand->setRowWidth(Config::handWidth, 0.25f);
				gameState->playerHand->runAction(MoveTo::create(0.25f, Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - Config::handOffsetY)));

				// Insert replaced cards back to deck
				for (auto it = this->replacedCards->begin(); it != this->replacedCards->end(); it++)
				{
					Card* card = *it;

					card->setScale(Card::cardScale);
					gameState->playerDeck->insertCardRandom(card, false, 0.0f);
				}
				break;
			}
			break;
	}
}

void ControlReplaceCards::initializeCardReplace(GameState* gameState)
{
	gameState->cardReplaceCount = std::min(3, gameState->playerDeck->getCardCount());
	this->replacedCards->clear();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	GameUtils::changeParent(gameState->playerHand, this, true);
	gameState->playerHand->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	gameState->playerHand->setCardScale(0.6f, 0.0f);
	gameState->playerHand->setRowWidth(Config::previewWidth, 0.25f);
}

void ControlReplaceCards::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(ControlReplaceCards::replaceCard, this));
}

void ControlReplaceCards::removeCardsOfType(Card* cardToRemove) 
{
	for (auto it = this->activeGameState->playerHand->rowCards->begin(); it != this->activeGameState->playerHand->rowCards->end();)
	{
		Card* card = *it;
		if (card->cardData->cardName == cardToRemove->cardData->cardName) 
		{
			this->replacedCards->insert(card);
			this->activeGameState->playerHand->removeCard(card);
		} else {
			it++;
		}
	}
}

CallFunc* ControlReplaceCards::getNextStateTransition() 
{
	CallFunc* stateTransition;
	GameState* gameState = this->activeGameState;
	
	if (this->activeGameState->cardReplaceCount <= 0)
	{
		stateTransition = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::CoinFlip);
		});
	}
	else
	{
		stateTransition = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::ControlReplaceCards);
		});
	}

	return stateTransition;
}

void ControlReplaceCards::replaceCard(Card* card)
{
	this->activeGameState->cardReplaceCount--;
	this->removeCardsOfType(card); // We want to banish all cards of this type from being redrawn
	
	// Run The animation
	Size visibleSize = Director::getInstance()->getVisibleSize();
	card->runAction(MoveTo::create(0.5f, Vec2(card->getPositionX(), -visibleSize.height/ 2.0f - 128.0f)));

	// Get Our Replacement Card
	Card* replacement = this->activeGameState->playerDeck->drawCard();
	GameUtils::changeParent(replacement, this, true);
	replacement->reveal();

	// Update the state and either re-enter this state or exit to coinflip
	CallFunc* stateTransition = this->getNextStateTransition();
	CardRow * hand = this->activeGameState->playerHand;
	this->runAction(Sequence::create(
		CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, replacement, Config::insertDelay)),
		DelayTime::create(Config::insertDelay),
		stateTransition,
		nullptr
	));
}
