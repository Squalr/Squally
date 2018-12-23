#include "DeckCardCountDisplay.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Deck.h"
#include "Scenes/Hexus/GameState.h"

using namespace cocos2d;

DeckCardCountDisplay* DeckCardCountDisplay::create()
{
	DeckCardCountDisplay* instance = new DeckCardCountDisplay();

	instance->autorelease();

	return instance;
}

DeckCardCountDisplay::DeckCardCountDisplay()
{
	this->playerDeckCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->playerDeckCardCountText = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1);
	this->enemyDeckCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->enemyDeckCardCountText = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1);

	this->playerDeckCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->playerDeckCardCountFrame->setContentSize(Size(48.0f, 32.0f));
	this->playerDeckCardCountText->setAlignment(TextHAlignment::LEFT);
	this->playerDeckCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->enemyDeckCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->enemyDeckCardCountFrame->setContentSize(Size(48.0f, 32.0f));
	this->enemyDeckCardCountText->setAlignment(TextHAlignment::LEFT);
	this->enemyDeckCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->playerDeckCardCountFrame);
	this->addChild(this->playerDeckCardCountText);
	this->addChild(this->enemyDeckCardCountFrame);
	this->addChild(this->enemyDeckCardCountText);
}

DeckCardCountDisplay::~DeckCardCountDisplay()
{
}

void DeckCardCountDisplay::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerDeckCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f, visibleSize.height / 2.0f - Config::deckOffsetY - Config::deckCardCountOffsetY - 32.0f);
	this->playerDeckCardCountText->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f - Config::deckOffsetY - Config::deckCardCountOffsetY);

	this->enemyDeckCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f, visibleSize.height / 2.0f + Config::deckOffsetY + Config::deckCardCountOffsetY);
	this->enemyDeckCardCountText->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::deckOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f + Config::deckOffsetY + Config::deckCardCountOffsetY + 32.0f);
}

void DeckCardCountDisplay::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void DeckCardCountDisplay::onAnyStateChange(GameState* gameState)
{
	this->updateTotals(gameState);
}

void DeckCardCountDisplay::updateTotals(GameState* gameState)
{
	this->playerDeckCardCountText->setString(StrUtils::toStringZeroPad(gameState->playerDeck->getCardCount(), 2));
	this->enemyDeckCardCountText->setString(StrUtils::toStringZeroPad(gameState->enemyDeck->getCardCount(), 2));
}
