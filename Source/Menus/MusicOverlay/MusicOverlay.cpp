#include "MusicOverlay.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

MusicOverlay* MusicOverlay::create()
{
	MusicOverlay* instance = new MusicOverlay();

	instance->autorelease();

	return instance;
}

MusicOverlay::MusicOverlay()
{
	this->activeSongString = Strings::Constant;
	this->activeSongLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, this->activeSongString);

	this->addChild(this->activeSongLabel);
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
