#include "DeckCardCountDisplay.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Hexus/Deck.h"
#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/HexusConfig.h"

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
	this->playerDeckCardCountStr = ConstantString::create("0");
	this->playerDeckCardCountLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, this->playerDeckCardCountStr);
	this->enemyDeckCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->enemyDeckCardCountStr = ConstantString::create("0");
	this->enemyDeckCardCountLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, this->enemyDeckCardCountStr);

	this->playerDeckCardCountFrame->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->playerDeckCardCountFrame->setContentSize(CSize(48.0f, 32.0f));
	this->playerDeckCardCountLabel->setAlignment(TextHAlignment::CENTER);
	this->playerDeckCardCountLabel->setVerticalAlignment(TextVAlignment::CENTER);
	this->playerDeckCardCountLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->enemyDeckCardCountFrame->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->enemyDeckCardCountFrame->setContentSize(CSize(48.0f, 32.0f));
	this->enemyDeckCardCountLabel->setAlignment(TextHAlignment::CENTER);
	this->enemyDeckCardCountLabel->setVerticalAlignment(TextVAlignment::CENTER);
	this->enemyDeckCardCountLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->playerDeckCardCountFrame);
	this->playerDeckCardCountFrame->addChild(this->playerDeckCardCountLabel);
	this->addChild(this->enemyDeckCardCountFrame);
	this->enemyDeckCardCountFrame->addChild(this->enemyDeckCardCountLabel);
}

DeckCardCountDisplay::~DeckCardCountDisplay()
{
}

void DeckCardCountDisplay::initializePositions()
{
	super::initializePositions();

	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->playerDeckCardCountFrame->setPosition(visibleSize.width / 2.0f + HexusConfig::rightColumnCenter + HexusConfig::deckOffsetX - 24.0f, visibleSize.height / 2.0f - HexusConfig::deckOffsetY - HexusConfig::deckCardCountOffsetY - 32.0f);
	this->playerDeckCardCountLabel->setPosition(Vec2(8.0f, this->playerDeckCardCountFrame->getContentSize().height / 2.0f));

	this->enemyDeckCardCountFrame->setPosition(visibleSize.width / 2.0f + HexusConfig::rightColumnCenter + HexusConfig::deckOffsetX - 24.0f, visibleSize.height / 2.0f + HexusConfig::deckOffsetY + HexusConfig::deckCardCountOffsetY);
	this->enemyDeckCardCountLabel->setPosition(Vec2(8.0f, this->enemyDeckCardCountFrame->getContentSize().height / 2.0f));
}

void DeckCardCountDisplay::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void DeckCardCountDisplay::onAnyStateChange(GameState* gameState)
{
	this->updateTotals(gameState);
}

void DeckCardCountDisplay::updateTotals(GameState* gameState)
{
	this->playerDeckCardCountStr->setString(StrUtils::toStringZeroPad(gameState->playerDeck->getCardCount(), 2));
	this->enemyDeckCardCountStr->setString(StrUtils::toStringZeroPad(gameState->enemyDeck->getCardCount(), 2));
}
