#include "StateCardReplace.h"
#include <algorithm>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/HUD/FocusTakeOver.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Deck.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

StateCardReplace* StateCardReplace::create()
{
	StateCardReplace* instance = new StateCardReplace();

	instance->autorelease();

	return instance;
}

StateCardReplace::StateCardReplace() : super(GameState::StateType::CardReplace)
{
	LocalizedLabel* doneButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Done::create());
	LocalizedLabel* doneButtonLabelHover = doneButtonLabel->clone();
	
	this->removedCards = std::vector<Card*>();
	doneButtonLabel->enableOutline(Color4B::BLACK, 2);
	doneButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->doneButton = ClickableTextNode::create(
		doneButtonLabel,
		doneButtonLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected
	);
	this->focusTakeOver = FocusTakeOver::create();
	
	this->addChild(this->focusTakeOver);
	this->addChild(this->doneButton);
}

StateCardReplace::~StateCardReplace()
{
}

void StateCardReplace::onEnter()
{
	super::onEnter();

	this->doneButton->setOpacity(0);
}

void StateCardReplace::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->doneButton->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + 24.0f);
}

void StateCardReplace::onEndReplaceCards(GameState* gameState)
{
	gameState->cardReplaceCount = 0;

	GameState::updateState(gameState, GameState::StateType::CoinFlip);
}

void StateCardReplace::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);

	if (gameState->roundNumber == 0)
	{
		gameState->cardReplaceCount = std::min(HexusConfig::initialCardReplacements, gameState->playerDeck->getCardCount());
	}
	else
	{
		gameState->cardReplaceCount = std::min(HexusConfig::midgameCardReplacements, gameState->playerDeck->getCardCount());
	}
}

void StateCardReplace::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	if (gameState->cardReplaceCount > 0)
	{
		this->doneButton->enableInteraction(0);
		this->doneButton->runAction(FadeTo::create(HexusConfig::replaceEndButtonFadeSpeed, 255));

		Size visibleSize = Director::getInstance()->getVisibleSize();

		this->focusTakeOver->focus({
			gameState->playerHand,
			gameState->enemyHand,
		});

		gameState->playerHand->runAction(MoveTo::create(0.25f, Vec2(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f - 192.0f)));
		gameState->playerHand->setCardScale(0.6f, 0.25f);
		gameState->playerHand->setRowWidth(HexusConfig::previewWidth, 0.25f);
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
	super::onStateReload(gameState);

	if (gameState->cardReplaceCount > 0)
	{
		this->doneButton->enableInteraction();
		gameState->playerHand->enableRowCardInteraction();

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
	super::onStateExit(gameState);

	// Restore hand to proper position
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->focusTakeOver->unfocus();
	gameState->playerHand->setCardScale(Card::cardScale, 0.25f);
	gameState->playerHand->setRowWidth(HexusConfig::handWidth, 0.25f);
	gameState->playerHand->runAction(MoveTo::create(0.25f, Vec2(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f - HexusConfig::handOffsetY)));

	// Shuffle player deck
	gameState->playerDeck->shuffle();

	// Hide Done Button
	this->doneButton->disableInteraction(this->doneButton->getOpacity());
	this->doneButton->runAction(FadeTo::create(HexusConfig::replaceEndButtonFadeSpeed, 0));
}

void StateCardReplace::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateCardReplace::replaceCard, this, gameState));
	this->doneButton->setMouseClickCallback(CC_CALLBACK_0(StateCardReplace::onEndReplaceCards, this, gameState));
}

void StateCardReplace::replaceCard(Card* cardToReplace, GameState* gameState)
{
	if (gameState->cardReplaceCount > 0)
	{
		this->doneButton->disableInteraction();

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
		for (auto card : this->removedCards)
		{
			gameState->playerDeck->insertCardBottom(card, false, 0.5f);
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

		// Either exit this state, or re-enter if not finished
		if (gameState->cardReplaceCount <= 0)
		{
			gameState->playerHand->disableRowCardInteraction();

			// Finished replacing cards
			CardRow * hand = gameState->playerHand;
			this->runAction(Sequence::create(
				CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, replacement, HexusConfig::insertDelay)),
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
				CallFunc::create(CC_CALLBACK_0(CardRow::insertCard, hand, replacement, HexusConfig::insertDelay)),
				DelayTime::create(HexusConfig::insertDelay),
				CallFunc::create([=]
				{
					GameState::updateState(gameState, GameState::StateType::CardReplace);
				}),
				nullptr
			));
		}
	}
}
