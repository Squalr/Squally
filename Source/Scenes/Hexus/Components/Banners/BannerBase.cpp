#include "BannerBase.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Strings/Strings.h"

using namespace cocos2d;

BannerBase* BannerBase::create()
{
	BannerBase* instance = new BannerBase();

	instance->autorelease();

	return instance;
}

BannerBase::BannerBase()
{
	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->bannerOverlay = LayerColor::create(Color4B(0, 0, 0, 127), visibleSize.width, 144.0f);
	this->bannerLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M2, Strings::Common_Empty::create());
	this->bannerChildrenNode = Node::create();

	this->bannerLabel->enableOutline(Color4B::BLACK, 4);

	this->addChild(this->bannerOverlay);
	this->addChild(this->bannerChildrenNode);
	this->addChild(this->bannerLabel);
}

BannerBase::~BannerBase()
{
}

void BannerBase::onEnter()
{
	super::onEnter();

	this->bannerOverlay->setOpacity(0);
	this->bannerLabel->setOpacity(0);
	this->bannerChildrenNode->setOpacity(0);
}

void BannerBase::initializePositions()
{
	super::initializePositions();

	CSize visibleSize = Director::getInstance()->getVisibleSize();

	this->bannerOverlay->setPosition(0.0f, visibleSize.height / 2.0f - this->bannerOverlay->getContentSize().height / 2 + 320.0f);
	this->bannerLabel->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + 320.0f);
}

void BannerBase::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void BannerBase::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void BannerBase::setBannerText(LocalizedString* text)
{
	this->bannerLabel->setLocalizedString(text);
}

void BannerBase::flashBanner()
{
	this->bannerLabel->runAction(Sequence::create(
		FadeTo::create(HexusConfig::bannerFadeSpeed, 255),
		DelayTime::create(HexusConfig::bannerDisplayDuration),
		FadeTo::create(HexusConfig::bannerFadeSpeed, 0),
		nullptr
	));

	this->bannerOverlay->runAction(Sequence::create(
		FadeTo::create(HexusConfig::bannerFadeSpeed, 196),
		DelayTime::create(HexusConfig::bannerDisplayDuration),
		FadeTo::create(HexusConfig::bannerFadeSpeed, 0),
		nullptr
	));

	this->bannerChildrenNode->runAction(Sequence::create(
		FadeTo::create(HexusConfig::bannerFadeSpeed, 255),
		DelayTime::create(HexusConfig::bannerDisplayDuration),
		FadeTo::create(HexusConfig::bannerFadeSpeed, 0),
		nullptr
	));
}

void BannerBase::showBanner()
{
	this->bannerLabel->runAction(Sequence::create(
		FadeTo::create(HexusConfig::bannerFadeSpeed, 255),
		nullptr
	));

	this->bannerOverlay->runAction(Sequence::create(
		FadeTo::create(HexusConfig::bannerFadeSpeed, 196),
		nullptr
	));

	this->bannerChildrenNode->runAction(Sequence::create(
		FadeTo::create(HexusConfig::bannerFadeSpeed, 255),
		nullptr
	));
}

void BannerBase::hideBanner()
{
	this->bannerLabel->runAction(Sequence::create(
		FadeTo::create(HexusConfig::bannerFadeSpeed, 0),
		nullptr
	));

	this->bannerOverlay->runAction(Sequence::create(
		FadeTo::create(HexusConfig::bannerFadeSpeed, 0),
		nullptr
	));

	this->bannerChildrenNode->runAction(Sequence::create(
		FadeTo::create(HexusConfig::bannerFadeSpeed, 0),
		nullptr
	));
}

void BannerBase::addBannerChild(Node* child)
{
	this->bannerChildrenNode->addChild(child);
}
