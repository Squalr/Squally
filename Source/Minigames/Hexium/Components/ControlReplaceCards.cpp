#include "ControlReplaceCards.h"

ControlReplaceCards* ControlReplaceCards::create()
{
	ControlReplaceCards* controlReplaceCards = new ControlReplaceCards();

	controlReplaceCards->autorelease();

	return controlReplaceCards;
}

ControlReplaceCards::ControlReplaceCards()
{
	this->replacedCards = new std::set<Card*>();
}

ControlReplaceCards::~ControlReplaceCards()
{
	delete(this->replacedCards);
}

void ControlReplaceCards::onEnter()
{
	ComponentBase::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void ControlReplaceCards::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void ControlReplaceCards::initializeListeners()
{
}

void ControlReplaceCards::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	switch (gameState->stateType) {
	case GameState::StateType::ControlReplaceCards:
		if (gameState->stateType != gameState->previousStateType)
		{
			this->initializeCardReplace(gameState);
		}
		this->initializeCallbacks(gameState);
		break;
	}
}

void ControlReplaceCards::initializeCardReplace(GameState* gameState)
{
	this->replaceCount = std::min(2, gameState->playerDeck->getCardCount());
	this->replacedCards->clear();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	gameState->playerHand->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	for (auto it = gameState->playerHand->rowCards->begin(); it != gameState->playerHand->rowCards->end(); it++)
	{
		Card* card = *it;

		card->setScale(0.75f);
	}
}

void ControlReplaceCards::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(ControlReplaceCards::replaceCard, this));
}

void ControlReplaceCards::replaceCard(Card* card)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->replaceCount--;
	this->replacedCards->insert(card);
	this->activeGameState->playerHand->removeCard(card);

	card->runAction(MoveTo::create(0.5f, Vec2(card->getPositionX(), visibleSize.height)));

	CallFunc* stateTransition;
	
	if (this->replaceCount <= 0)
	{
		GameState* gameState = this->activeGameState;

		stateTransition = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::CoinFlip);
		});
	}
	else
	{
		GameState* gameState = this->activeGameState;

		stateTransition = CallFunc::create([gameState]
		{
			GameState::updateState(gameState, GameState::StateType::ControlReplaceCards);
		});
	}

	Card* replacement = this->activeGameState->playerDeck->drawCard();
	CardRow * hand = this->activeGameState->playerHand;

	GameUtils::changeParent(replacement, this, true);

	this->runAction(Sequence::create(
		CallFunc::create(CC_CALLBACK_0(Card::doDrawAnimation, replacement, Config::cardDrawDelay)),
		DelayTime::create(Config::cardDrawDelay),
		DelayTime::create(Config::revealDelay),
		CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, replacement, Config::insertDelay)),
		DelayTime::create(Config::insertDelay),
		stateTransition,
		nullptr
	));
}
