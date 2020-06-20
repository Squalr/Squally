#include "InteractMenu.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

InteractMenu* InteractMenu::create(LocalizedString* displayString, Color3B backColor, float menuWidth)
{
	InteractMenu* instance = new InteractMenu(displayString, backColor, menuWidth);

	instance->autorelease();

	return instance;
}

InteractMenu::InteractMenu(LocalizedString* displayString, Color3B backColor, float menuWidth)
{
	this->uiElements = Node::create();
	this->displayString = displayString;
	this->displayLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, this->displayString);
	this->menuSize = Size(menuWidth, 48.0f);
	this->backdrop = LayerColor::create(Color4B(backColor.r, backColor.g, backColor.b, 196), this->menuSize.width, this->menuSize.height);
	this->hasRelocated = false;
	this->isFadingIn = false;
	this->isFadingOut = false;

	this->displayLabel->setHorizontalAlignment(TextHAlignment::CENTER);
	this->displayLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->uiElements->setOpacity(0);

	this->uiElements->addChild(this->backdrop);
	this->uiElements->addChild(this->displayLabel);
	this->addChild(this->uiElements);
}

InteractMenu::~InteractMenu()
{
}

void InteractMenu::onEnter()
{
	super::onEnter();

	this->setOpacity(0);
}

void InteractMenu::onExit()
{
	super::onExit();
}

void InteractMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->backdrop->setPosition(Vec2(-this->menuSize.width / 2.0f, -this->menuSize.height / 2.0f));
	this->uiElements->setPosition(Vec2(0.0f, 144.0f));
}

void InteractMenu::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeEnable, [=](EventCustom* eventCustom)
	{
		this->uiElements->setVisible(false);
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeDisable, [=](EventCustom* eventCustom)
	{
		this->uiElements->setVisible(true);
	}));
}

void InteractMenu::show()
{
	if (this->isShowing() || this->isFadingIn)
	{
		return;
	}
	
	this->tryRelocate();

	this->isFadingIn = true;
	this->isFadingOut = false;

	this->uiElements->runAction(Sequence::create(
		FadeTo::create(0.15f, 255),
		CallFunc::create([=]()
		{
			this->isFadingIn = false;
		}),
		nullptr
	));

	this->uiElements->runAction(FadeTo::create(0.15f, 255));
}

void InteractMenu::hide()
{
	if (this->isHidden() || this->isFadingOut)
	{
		return;
	}
	
	this->tryRelocate();

	this->isFadingOut = true;
	this->isFadingIn = false;

	this->uiElements->runAction(Sequence::create(
		FadeTo::create(0.15f, 0),
		CallFunc::create([=]()
		{
			this->isFadingOut = false;
		}),
		nullptr
	));
}

void InteractMenu::tryRelocate()
{
	if (!this->hasRelocated)
	{
		// Move the UI elements to the top-most layer
		ObjectEvents::TriggerBindObjectToUI(ObjectEvents::RelocateObjectArgs(
			this->uiElements
		));
		this->hasRelocated = true;
	}
}

bool InteractMenu::isHidden()
{
	return this->uiElements->getOpacity() <= 0;
}

bool InteractMenu::isShowing()
{
	return this->uiElements->getOpacity() >= 255;
}
