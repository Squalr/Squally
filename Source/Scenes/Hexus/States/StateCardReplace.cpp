#include "StateCardReplace.h"

StateCardReplace* StateCardReplace::create()
{
	StateCardReplace* instance = new StateCardReplace();

	instance->autorelease();

	return instance;
}

StateCardReplace::StateCardReplace() : StateBase(GameState::StateType::CardReplace)
{
	Label* doneButtonLabel = Label::create("Done", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* doneButtonLabelHover = Label::create("Done", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* doneButtonLabelClick = Label::create("Done", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	
	this->removedCards = std::vector<Card*>();
	doneButtonLabel->enableOutline(Color4B::BLACK, 2);
	doneButtonLabelHover->enableOutline(Color4B::BLACK, 2);
	doneButtonLabelClick->enableOutline(Color4B::BLACK, 2);

	this->doneButton = TextMenuSprite::create(
		doneButtonLabel,
		doneButtonLabelHover,
		doneButtonLabelClick,
		Resources::Minigames_Hexus_ButtonPlank,
		Resources::Minigames_Hexus_ButtonPlankHover,
		Resources::Minigames_Hexus_ButtonPlankClick
	);
	this->doneButton->setOpacity(0);
	
	this->addChild(this->doneButton);
}

StateCardReplace::~StateCardReplace()
{
}

void StateCardReplace::onEndReplaceCards(MenuSprite* menuSprite, GameState* gameState)
{
	gameState->cardReplaceCount = 0;

	GameState::updateState(gameState, GameState::StateType::CoinFlip);
}

void StateCardReplace::initializePositions()
{
	StateBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->doneButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 200.0f);
}

void StateCardReplace::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);

	if (gameState->roundNumber == 0)
	{
		gameState->cardReplaceCount = std::min(Config::initialCardReplacements, gameState->playerDeck->getCardCount());
	}
	else
	{
		gameState->cardReplaceCount = std::min(Config::midgameCardReplacements, gameState->playerDeck->getCardCount());
	}
}

void StateCardReplace::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	if (gameState->cardReplaceCount > 0)
	{
		this->doneButton->enableInteraction(0);
		this->doneButton->runAction(FadeTo::create(Config::replaceEndButtonFadeSpeed, 255));

		gameState->playerHand->enableRowCardInteraction();

		Size visibleSize = Director::getInstance()->getVisibleSize();
		GameUtils::changeParent(gameState->playerHand, this, true);
		gameState->playerHand->runAction(MoveTo::create(0.25f, Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f)));
		gameState->playerHand->setCardScale(0.6f, 0.25f);
		gameState->playerHand->setRowWidth(Config::previewWidth, 0.25f);
		gameState->playerHand->enableRowCardInteraction();

		gameState = gameState;
		this->initializeCallbacks(gameState);
	}
	else
	{
		this->runAction(Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([=]()
			{
				GameState::updateState(gameState, GameState::StateType::CoinFlip);
			}),
			nullptr
		));
	}
}

void StateCardReplace::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);

	if (gameState->cardReplaceCount > 0)
	{
		gameState->playerHand->enableRowCardInteraction();

		gameState = gameState;
		this->initializeCallbacks(gameState);
	}
	else
	{
		this->runAction(Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([=]()
			{
				GameState::updateState(gameState, GameState::StateType::CoinFlip);
			}),
			nullptr
		));
	}
}

void StateCardReplace::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);

	// Restore hand to proper position
	Size visibleSize = Director::getInstance()->getVisibleSize();
	GameUtils::changeParent(gameState->playerHand, gameState, true);
	gameState->playerHand->setCardScale(Card::cardScale, 0.25f);
	gameState->playerHand->setRowWidth(Config::handWidth, 0.25f);
	gameState->playerHand->runAction(MoveTo::create(0.25f, Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - Config::handOffsetY)));

	// Shuffle player deck
	gameState->playerDeck->shuffle();

	// Hide Done Button
	this->doneButton->disableInteraction(this->doneButton->getOpacity());
	this->doneButton->runAction(FadeTo::create(Config::replaceEndButtonFadeSpeed, 0));
}

void StateCardReplace::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateCardReplace::replaceCard, this, gameState));
	this->doneButton->setClickCallback(CC_CALLBACK_1(StateCardReplace::onEndReplaceCards, this, gameState));
}

void StateCardReplace::replaceCard(Card* cardToReplace, GameState* gameState)
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
			if (card->cardData->cardName == cardToReplace->cardData->cardName)
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
			this->runAction(Sequence::create(
				DelayTime::create(0.5f),
				CallFunc::create([=]
				{
					GameState::updateState(gameState, GameState::StateType::CoinFlip);
				}),
				nullptr
			));
			
			return;
		}

		GameUtils::changeParent(replacement, this, true);
		replacement->reveal();

		// Update the state and either re-enter this state or exit to coinflip
		if (gameState->cardReplaceCount <= 0)
		{
			gameState->playerHand->disableRowCardInteraction();

			// Finished replacing cards
			CardRow * hand = gameState->playerHand;
			this->runAction(Sequence::create(
				CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, replacement, Config::insertDelay)),
				DelayTime::create(0.75f),
				CallFunc::create([=]
				{
					GameState::updateState(gameState, GameState::StateType::CoinFlip);
				}),
				nullptr
			));
		}
		else
		{
			// Reload state
			CardRow * hand = gameState->playerHand;
			this->runAction(Sequence::create(
				CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, replacement, Config::insertDelay)),
				DelayTime::create(Config::insertDelay),
				CallFunc::create([=]
				{
					GameState::updateState(gameState, GameState::StateType::CardReplace);
				}),
				nullptr
			));
		}
	}
}
