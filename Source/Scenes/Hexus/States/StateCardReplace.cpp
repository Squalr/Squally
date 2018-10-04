#include "StateCardReplace.h"

StateCardReplace* StateCardReplace::create()
{
	StateCardReplace* instance = new StateCardReplace();

	instance->autorelease();

	return instance;
}

StateCardReplace::StateCardReplace() : StateBase(GameState::StateType::CardReplace)
{
	this->replacedCards = new std::set<Card*>();
	Label* doneButtonLabel = Label::create("Done", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* doneButtonLabelHover = Label::create("Done", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* doneButtonLabelClick = Label::create("Done", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	
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
	delete(this->replacedCards);
}

void StateCardReplace::initializeListeners()
{
	StateBase::initializeListeners();

	this->doneButton->setClickCallback(CC_CALLBACK_1(StateCardReplace::onEndReplaceCards, this));
}

void StateCardReplace::onEndReplaceCards(MenuSprite* menuSprite)
{
	this->activeGameState->cardReplaceCount = 0;

	GameState::updateState(this->activeGameState, GameState::StateType::CoinFlip);
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
		gameState->cardReplaceCount = std::min(3, gameState->playerDeck->getCardCount());
	}
	else
	{
		gameState->cardReplaceCount = std::min(1, gameState->playerDeck->getCardCount());
	}
}

void StateCardReplace::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	this->doneButton->enableInteraction(0);
	this->doneButton->runAction(FadeTo::create(Config::replaceEndButtonFadeSpeed, 255));

	this->replacedCards->clear();
	gameState->playerHand->enableRowCardInteraction();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	GameUtils::changeParent(gameState->playerHand, this, true);
	gameState->playerHand->runAction(MoveTo::create(0.25f, Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f)));
	gameState->playerHand->setCardScale(0.6f, 0.25f);
	gameState->playerHand->setRowWidth(Config::previewWidth, 0.25f);
	gameState->playerHand->enableRowCardInteraction();

	this->activeGameState = gameState;
	this->initializeCallbacks(gameState);
}

void StateCardReplace::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);

	gameState->playerHand->enableRowCardInteraction();

	this->activeGameState = gameState;
	this->initializeCallbacks(gameState);
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

	// Insert replaced cards back to deck
	for (auto it = this->replacedCards->begin(); it != this->replacedCards->end(); it++)
	{
		Card* card = *it;

		card->setScale(Card::cardScale);
		gameState->playerDeck->insertCardRandom(card, false, 0.0f);
	}

	// Hide Done Button
	this->doneButton->disableInteraction(255);
	this->doneButton->runAction(FadeTo::create(Config::replaceEndButtonFadeSpeed, 0));
}

void StateCardReplace::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateCardReplace::replaceCard, this));
}

void StateCardReplace::replaceCard(Card* card)
{
	if (this->activeGameState->cardReplaceCount > 0)
	{
		this->activeGameState->cardReplaceCount--;
		this->replacedCards->insert(card);
		this->activeGameState->playerHand->removeCard(card);
		this->removeCardsOfTypeFromDeck(card, this->activeGameState->playerDeck); // We want to banish all cards of this type from being redrawn
	
		// Run The animation
		Size visibleSize = Director::getInstance()->getVisibleSize();
		card->runAction(MoveTo::create(0.5f, Vec2(card->getPositionX(), -visibleSize.height/ 2.0f - 128.0f)));

		// Get Our Replacement Card
		Card* replacement = this->activeGameState->playerDeck->drawCard();
		GameUtils::changeParent(replacement, this, true);
		replacement->reveal();

		// Update the state and either re-enter this state or exit to coinflip

		CallFunc* stateTransition = nullptr;

		if (this->activeGameState->cardReplaceCount <= 0)
		{
			stateTransition = CallFunc::create([=]
			{
				GameState::updateState(this->activeGameState, GameState::StateType::CoinFlip);
			});
		}
		else
		{
			// Reload state
			stateTransition = CallFunc::create([=]
			{
				GameState::updateState(this->activeGameState, GameState::StateType::CardReplace);
			});
		}

		CardRow * hand = this->activeGameState->playerHand;
		this->runAction(Sequence::create(
			CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, replacement, Config::insertDelay)),
			DelayTime::create(Config::insertDelay),
			stateTransition,
			nullptr
		));

		if (this->activeGameState->cardReplaceCount <= 0)
		{
			this->activeGameState->playerHand->disableRowCardInteraction();
		}
	}
}

void StateCardReplace::removeCardsOfTypeFromDeck(Card* cardToRemove, Deck* deck) 
{
	deck->removeCardsWhere([=](Card* card)
	{
		if (card->cardData->cardName == cardToRemove->cardData->cardName)
		{
			// We put the card into the replacedCards to be shuffled back into the deck at the end of mulligan
			this->replacedCards->insert(card);
			return true;
		}

		return false;
	});
}
