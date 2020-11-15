#include "HandCardCountDisplay.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/HexusResources.h"

using namespace cocos2d;

HandCardCountDisplay* HandCardCountDisplay::create()
{
	HandCardCountDisplay* instance = new HandCardCountDisplay();

	instance->autorelease();

	return instance;
}

HandCardCountDisplay::HandCardCountDisplay()
{
	this->playerHandCardIcon = Sprite::create(HexusResources::CardIcon);
	this->playerHandCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->playerHandCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->playerHandCardCountFrame->setContentSize(Size(80.0f, 32.0f));
	this->playerHandCardCountStr = ConstantString::create("0");
	this->playerHandCardCountLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, this->playerHandCardCountStr);
	this->playerHandCardCountLabel->setAlignment(TextHAlignment::LEFT);
	this->playerHandCardCountLabel->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->enemyHandCardIcon = Sprite::create(HexusResources::CardIcon);
	this->enemyHandCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->enemyHandCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->enemyHandCardCountFrame->setContentSize(Size(80.0f, 32.0f));
	this->enemyHandCardCountStr = ConstantString::create("0");
	this->enemyHandCardCountLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, this->enemyHandCardCountStr);
	this->enemyHandCardCountLabel->setAlignment(TextHAlignment::LEFT);
	this->enemyHandCardCountLabel->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->playerHandCardCountFrame);
	this->addChild(this->playerHandCardIcon);
	this->addChild(this->playerHandCardCountLabel);

	this->addChild(this->enemyHandCardCountFrame);
	this->addChild(this->enemyHandCardIcon);
	this->addChild(this->enemyHandCardCountLabel);
}

HandCardCountDisplay::~HandCardCountDisplay()
{
}

void HandCardCountDisplay::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerHandCardCountFrame->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::handCountOffsetX - 24.0f - 36.0f, visibleSize.height / 2.0f - HexusConfig::handCountOffsetY - 32.0f);
	this->playerHandCardIcon->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::handCountOffsetX - 40.0f, visibleSize.height / 2.0f - HexusConfig::handCountOffsetY - 16.0f);
	this->playerHandCardCountLabel->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::handCountOffsetX - 24.0f + 4.0f, visibleSize.height / 2.0f - HexusConfig::handCountOffsetY + 2.0f);

	this->enemyHandCardCountFrame->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::handCountOffsetX - 24.0f - 36.0f, visibleSize.height / 2.0f + HexusConfig::handCountOffsetY);
	this->enemyHandCardIcon->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::handCountOffsetX - 40.0f, visibleSize.height / 2.0f + HexusConfig::handCountOffsetY + 16.0f);
	this->enemyHandCardCountLabel->setPosition(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + HexusConfig::handCountOffsetX - 24.0f + 4.0f, visibleSize.height / 2.0f + HexusConfig::handCountOffsetY + 32.0f + 2.0f);
}

void HandCardCountDisplay::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void HandCardCountDisplay::onAnyStateChange(GameState* gameState)
{
	this->updateTotals(gameState);
}

void HandCardCountDisplay::updateTotals(GameState* gameState)
{
	this->playerHandCardCountStr->setString(StrUtils::toStringZeroPad(gameState->playerHand->getCardCount(), 2));
	this->enemyHandCardCountStr->setString(StrUtils::toStringZeroPad(gameState->enemyHand->getCardCount(), 2));
}
