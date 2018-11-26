#include "HandCardCountDisplay.h"

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
	this->playerHandCardCountText = Label::create("", Localization::getCodingFont(), 32.0f);
	this->playerHandCardCountText->setAlignment(TextHAlignment::LEFT);
	this->playerHandCardCountText->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->enemyHandCardIcon = Sprite::create(HexusResources::CardIcons);
	this->enemyHandCardCountFrame = LayerColor::create(Color4B(0, 0, 0, 196));
	this->enemyHandCardCountFrame->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->enemyHandCardCountFrame->setContentSize(Size(80.0f, 32.0f));
	this->enemyHandCardCountText = Label::create("", Localization::getCodingFont(), 32.0f);
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
	ComponentBase::initializePositions();

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
	ComponentBase::onBeforeStateChange(gameState);
}

void HandCardCountDisplay::onAnyStateChange(GameState* gameState)
{
	this->updateTotals(gameState);
}

void HandCardCountDisplay::updateTotals(GameState* gameState)
{
	this->playerHandCardCountText->setString(StrUtils::toStringZeroPad(gameState->playerHand->getCardCount(), 2));
	this->enemyHandCardCountText->setString(StrUtils::toStringZeroPad(gameState->enemyHand->getCardCount(), 2));
}
