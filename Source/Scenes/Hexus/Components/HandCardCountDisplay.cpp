#include "HandCardCountDisplay.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/GameState.h"

#include "Resources/HexusResources.h"

#include "Strings/Generics/Constant.h"

using namespace cocos2d;

HandCardCountDisplay* HandCardCountDisplay::create()
{
	HandCardCountDisplay* instance = new HandCardCountDisplay();

	instance->autorelease();

	return instance;
}

HandCardCountDisplay::HandCardCountDisplay()
{
	this->playerHandCardIcon = Sprite::create(HexusResources::CardIcons);
	this->playerHandCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->playerHandCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->playerHandCardCountFrame->setContentSize(Size(80.0f, 32.0f));
	this->playerHandCardCountText = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Generics_Constant::create());
	this->playerHandCardCountText->setAlignment(TextHAlignment::LEFT);
	this->playerHandCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->enemyHandCardIcon = Sprite::create(HexusResources::CardIcons);
	this->enemyHandCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->enemyHandCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->enemyHandCardCountFrame->setContentSize(Size(80.0f, 32.0f));
	this->enemyHandCardCountText = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, Strings::Generics_Constant::create());
	this->enemyHandCardCountText->setAlignment(TextHAlignment::LEFT);
	this->enemyHandCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->playerHandCardCountFrame);
	this->addChild(this->playerHandCardIcon);
	this->addChild(this->playerHandCardCountText);

	this->addChild(this->enemyHandCardCountFrame);
	this->addChild(this->enemyHandCardIcon);
	this->addChild(this->enemyHandCardCountText);
}

HandCardCountDisplay::~HandCardCountDisplay()
{
}

void HandCardCountDisplay::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->playerHandCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 24.0f - 36.0f, visibleSize.height / 2.0f - Config::handCountOffsetY - 32.0f);
	this->playerHandCardIcon->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 40.0f, visibleSize.height / 2.0f - Config::handCountOffsetY - 16.0f);
	this->playerHandCardCountText->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f - Config::handCountOffsetY);

	this->enemyHandCardCountFrame->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 24.0f - 36.0f, visibleSize.height / 2.0f + Config::handCountOffsetY);
	this->enemyHandCardIcon->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 40.0f, visibleSize.height / 2.0f + Config::handCountOffsetY + 16.0f);
	this->enemyHandCardCountText->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::handCountOffsetX - 24.0f + 8.0f, visibleSize.height / 2.0f + Config::handCountOffsetY + 32.0f);
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
	this->playerHandCardCountText->setStringReplacementVariables(ConstantString::create(StrUtils::toStringZeroPad(gameState->playerHand->getCardCount(), 2)));
	this->enemyHandCardCountText->setStringReplacementVariables(ConstantString::create(StrUtils::toStringZeroPad(gameState->enemyHand->getCardCount(), 2)));
}
