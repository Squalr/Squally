#include "BannerBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/Config.h"

using namespace cocos2d;

BannerBase* BannerBase::create()
{
	BannerBase* instance = new BannerBase();

	instance->autorelease();

	return instance;
}

BannerBase::BannerBase()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->statusBanner = LayerColor::create(Color4B(0, 0, 0, 127), visibleSize.width, 144.0f);
	this->statusLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M2);
	this->bannerChildrenNode = Node::create();

	this->statusBanner->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->statusLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->statusLabel->enableOutline(Color4B::BLACK, 4);

	this->addChild(this->statusBanner);
	this->addChild(this->bannerChildrenNode);
	this->addChild(this->statusLabel);
}

BannerBase::~BannerBase()
{
}

void BannerBase::onEnter()
{
	ComponentBase::onEnter();

	this->statusBanner->setOpacity(0);
	this->statusLabel->setOpacity(0);
	this->bannerChildrenNode->setOpacity(0);
}

void BannerBase::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->statusBanner->setPosition(0.0f, visibleSize.height / 2.0f - this->statusBanner->getContentSize().height / 2 + 320.0f);
	this->statusLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 320.0f);
}

void BannerBase::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void BannerBase::onAnyStateChange(GameState* gameState)
{
	ComponentBase::onAnyStateChange(gameState);
}

void BannerBase::setBannerText(LocalizedString* text)
{
	this->statusLabel->setLocalizedString(text);
}

void BannerBase::flashBanner()
{
	this->statusLabel->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));

	this->statusBanner->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 196),
		DelayTime::create(Config::bannerDisplayDuration),
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));

	this->bannerChildrenNode->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		DelayTime::create(Config::bannerDisplayDuration),
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));
}

void BannerBase::showBanner()
{
	this->statusLabel->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		nullptr
	));

	this->statusBanner->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 196),
		nullptr
	));

	this->bannerChildrenNode->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 255),
		nullptr
	));
}

void BannerBase::hideBanner()
{
	this->statusLabel->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));

	this->statusBanner->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));

	this->bannerChildrenNode->runAction(Sequence::create(
		FadeTo::create(Config::bannerFadeSpeed, 0),
		nullptr
	));
}

void BannerBase::addBannerChild(Node* child)
{
	this->bannerChildrenNode->addChild(child);
}
