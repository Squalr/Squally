#include "HackButton.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

HackButton* HackButton::create()
{
	HackButton* instance = new HackButton();

	instance->autorelease();

	return instance;
}

HackButton::HackButton() : ClickableNode(Sprite::create(UIResources::Menus_Buttons_HackButton), Sprite::create(UIResources::Menus_Buttons_HackButtonHover))
{
}

HackButton::~HackButton()
{
}

void HackButton::addEventListener(cocos2d::EventListener* listener)
{
	// Here's the magic trick -- we want the hackable button to be clickable no matter what
	this->addEventListenerIgnorePause(listener);
}

void HackButton::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeEnable, [=](EventCustom* eventCustom)
	{
		this->disableInteraction();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackableObjectOpen, [=](EventCustom* eventCustom)
	{
		this->disableInteraction();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackableObjectClose, [=](EventCustom* eventCustom)
	{
		this->enableInteraction();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeDisable, [=](EventCustom* eventCustom)
	{
		this->enableInteraction();
	}));
}
