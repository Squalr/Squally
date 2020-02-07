#include "MusicOverlay.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Strings/Strings.h"

using namespace cocos2d;

MusicOverlay* MusicOverlay::create()
{
	MusicOverlay* instance = new MusicOverlay();

	instance->autorelease();

	return instance;
}

MusicOverlay::MusicOverlay()
{
	this->trackString = Strings::Menus_Music_Track::create()->setStringReplacementVariables(ConstantString::create(""));
	this->artistString = Strings::Menus_Music_Artist::create()->setStringReplacementVariables(ConstantString::create(""));
	this->trackLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, this->trackString);
	this->artistLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, this->trackString);

	this->trackLabel->enableOutline(Color4B::BLACK, 2);
	this->artistLabel->enableOutline(Color4B::BLACK, 2);

	this->trackLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->artistLabel->setAnchorPoint(Vec2(1.0f, 0.5f));

	this->addChild(this->trackLabel);
	this->addChild(this->artistLabel);
}

MusicOverlay::~MusicOverlay()
{
}

void MusicOverlay::onEnter()
{
	super::onEnter();
}

void MusicOverlay::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->trackLabel->setPosition(Vec2(visibleSize.width - 48.0f, 96.0f));
	this->artistLabel->setPosition(Vec2(visibleSize.width - 48.0f, 96.0f - 32.0f));
}

void MusicOverlay::initializeListeners()
{
	super::initializeListeners();

	/*
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventHudTrackEntity, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::HudTrackEntityArgs* args = static_cast<PlatformerEvents::HudTrackEntityArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
		}
	}));
	*/
}
