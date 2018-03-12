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

	this->bannerBackground = LayerColor::create(Color4B(0, 0, 0, 127), 1920.0f, 144.0f);
	this->bannerLabel = Label::create("", Resources::Fonts_Montserrat_Medium, 48.0f);

	this->bannerBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->bannerLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->bannerBackground->setOpacity(0);
	this->bannerLabel->setOpacity(0);

	this->addChild(this->bannerBackground);
	this->addChild(this->bannerLabel);
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

	this->bannerBackground->setPosition(0.0f, visibleSize.height / 2.0f - this->bannerBackground->getContentSize().height / 2 + 320.0f);
	this->bannerLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 320.0f);
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

		if (this->replaceCount == 1)
		{
			this->bannerLabel->setString("REPLACE " + std::to_string(this->replaceCount) + " MORE CARD");
		}
		else
		{
			this->bannerLabel->setString("REPLACE " + std::to_string(this->replaceCount) + " MORE CARDS");
		}

		this->bannerLabel->runAction(Sequence::create(
			FadeTo::create(Config::bannerFadeSpeed, 255),
			nullptr
		));

		this->bannerBackground->runAction(Sequence::create(
			FadeTo::create(Config::bannerFadeSpeed, 127),
			nullptr
		));
		break;
	}
	switch (gameState->previousStateType) {
	case GameState::StateType::ControlReplaceCards:
		if (gameState->stateType == GameState::StateType::ControlReplaceCards)
		{
			break;
		}

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

		this->bannerLabel->runAction(Sequence::create(
			FadeTo::create(Config::bannerFadeSpeed, 0),
			nullptr
		));

		this->bannerBackground->runAction(Sequence::create(
			FadeTo::create(Config::bannerFadeSpeed, 0),
			nullptr
		));
		break;
	}
}

void ControlReplaceCards::initializeCardReplace(GameState* gameState)
{
	this->replaceCount = std::min(2, gameState->playerDeck->getCardCount());
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

void ControlReplaceCards::replaceCard(Card* card)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->replaceCount--;
	this->replacedCards->insert(card);
	this->activeGameState->playerHand->removeCard(card);

	card->runAction(MoveTo::create(0.5f, Vec2(card->getPositionX(), -visibleSize.height/ 2.0f - 128.0f)));

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

	replacement->reveal();

	this->runAction(Sequence::create(
		CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, replacement, Config::insertDelay)),
		DelayTime::create(Config::insertDelay),
		stateTransition,
		nullptr
	));
}
