#include "NotificationHud.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"

#include "Resources/UIResources.h"

#include "Strings/Common/Empty.h"
#include "Strings/Menus/Okay.h"

using namespace cocos2d;

NotificationHud* NotificationHud::create()
{
	NotificationHud* instance = new NotificationHud();

	instance->autorelease();

	return instance;
}

NotificationHud::NotificationHud()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->previousFocus = nullptr;
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 192), visibleSize.width, visibleSize.height);
	this->menuBack = Sprite::create(UIResources::Menus_ConfirmMenu_ConfirmMenu);
	this->title = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Common_Empty::create());
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Common_Empty::create(), Size(560.0f, 0.0f));

	LocalizedLabel* okLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Okay::create());
	LocalizedLabel* okLabelSelected = okLabel->clone();

	okLabel->enableOutline(Color4B::BLACK);
	okLabelSelected->enableOutline(Color4B::BLACK);

	this->okButton = ClickableTextNode::create(okLabel, okLabelSelected, UIResources::Menus_Buttons_WoodButton, UIResources::Menus_Buttons_WoodButtonSelected);

	this->title->enableOutline(Color4B::BLACK, 2);
	this->description->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->backdrop);
	this->addChild(this->menuBack);
	this->addChild(this->title);
	this->addChild(this->description);
	this->addChild(this->okButton);
}

NotificationHud::~NotificationHud()
{
}

void NotificationHud::onEnter()
{
	super::onEnter();

	this->setVisible(false);
}

void NotificationHud::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->menuBack->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->okButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 192.0f));
	this->title->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2 + 192.0f));
	this->description->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2 + 32.0f));
}

void NotificationHud::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventNotificationTakeover, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::NotificationTakeoverArgs* args = static_cast<PlatformerEvents::NotificationTakeoverArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->showNotificationMenu(args->title, args->description);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventNotification, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::NotificationArgs* args = static_cast<PlatformerEvents::NotificationArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
		}
	}));

	this->okButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->setVisible(false);

		if (this->previousFocus != nullptr)
		{
			GameUtils::focus(this->previousFocus);
		}
	});
}

void NotificationHud::showNotificationMenu(LocalizedString* title, LocalizedString* description)
{
	this->title->setLocalizedString(title);
	this->description->setLocalizedString(description);
	this->setVisible(true);
	
	this->previousFocus = GameUtils::getFocusedNode();
	GameUtils::focus(this);
}
