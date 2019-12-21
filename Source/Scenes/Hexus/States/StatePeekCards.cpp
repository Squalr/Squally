#include "StatePeekCards.h"
#include <algorithm>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Deck.h"
#include "Scenes/Hexus/States/StatePlayCard.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

StatePeekCards* StatePeekCards::create()
{
	StatePeekCards* instance = new StatePeekCards();

	instance->autorelease();

	return instance;
}

StatePeekCards::StatePeekCards() : super(GameState::StateType::PeekCards)
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
	
	this->addChild(this->doneButton);
}

StatePeekCards::~StatePeekCards()
{
}

void StatePeekCards::onEnter()
{
	super::onEnter();

	this->doneButton->setOpacity(0);
}

void StatePeekCards::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->doneButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 200.0f);
}

void StatePeekCards::onEndPeekCards(GameState* gameState)
{
	// Pick up from where we left off after playing this card
	StatePlayCard::DoNextTransition(gameState);
}

void StatePeekCards::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StatePeekCards::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);

	this->doneButton->enableInteraction(0);
	this->doneButton->runAction(FadeTo::create(Config::replaceEndButtonFadeSpeed, 255));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	GameUtils::changeParent(gameState->enemyHand, this, true);
	gameState->enemyHand->runAction(MoveTo::create(0.25f, Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f)));
	gameState->enemyHand->setCardScale(0.6f, 0.25f);
	gameState->enemyHand->setRowWidth(Config::previewWidth, 0.25f);
	gameState->enemyHand->enableRowCardInteraction();

	gameState = gameState;
	this->initializeCallbacks(gameState);
}

void StatePeekCards::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StatePeekCards::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);

	// Restore hand to proper position
	Size visibleSize = Director::getInstance()->getVisibleSize();
	GameUtils::changeParent(gameState->enemyHand, gameState, true);
	gameState->enemyHand->setCardScale(Card::cardScale, 0.25f);
	gameState->enemyHand->setRowWidth(Config::handWidth, 0.25f);
	gameState->enemyHand->runAction(MoveTo::create(0.25f, Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + Config::handOffsetY + 256.0f)));

	// Hide Done Button
	this->doneButton->disableInteraction(this->doneButton->getOpacity());
	this->doneButton->runAction(FadeTo::create(Config::replaceEndButtonFadeSpeed, 0));
}

void StatePeekCards::initializeCallbacks(GameState* gameState)
{
	this->doneButton->setMouseClickCallback(CC_CALLBACK_0(StatePeekCards::onEndPeekCards, this, gameState));
}

