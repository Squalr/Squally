#include "DefeatMenu.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Events/CombatEvents.h"

#include "Resources/UIResources.h"

#include "Strings/Combat/Defeat.h"
#include "Strings/Menus/Leave.h"

using namespace cocos2d;

DefeatMenu* DefeatMenu::create()
{
	DefeatMenu* instance = new DefeatMenu();

	instance->autorelease();

	return instance;
}

DefeatMenu::DefeatMenu()
{
	this->defeatBanner = Sprite::create(UIResources::Combat_DefeatBanner);
	this->defeatLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Combat_Defeat::create());

	LocalizedLabel*	okayLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Leave::create());
	LocalizedLabel*	okayLabelHover = okayLabel->clone();

	okayLabel->enableOutline(Color4B::BLACK, 2);
	okayLabelHover->enableOutline(Color4B::BLACK, 2);

	this->okayButton = ClickableTextNode::create(okayLabel, okayLabelHover, Sprite::create(UIResources::Menus_Buttons_GenericButton), Sprite::create(UIResources::Menus_Buttons_GenericButtonHover));

	this->defeatLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->defeatBanner);
	this->addChild(this->defeatLabel);
	this->addChild(this->okayButton);
}

DefeatMenu::~DefeatMenu()
{
}

void DefeatMenu::onEnter()
{
	super::onEnter();

	this->setVisible(false);
}

void DefeatMenu::initializePositions()
{
	super::initializePositions();

	this->defeatBanner->setPositionY(256.0f);
	this->defeatLabel->setPositionY(256.0f - 96.0f);
	this->okayButton->setPositionY(-128.0f);
}

void DefeatMenu::initializeListeners()
{
	super::initializeListeners();

	this->okayButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		CombatEvents::TriggerReturnToMap();
	});
}

void DefeatMenu::show()
{
	this->runAction(FadeTo::create(1.0f, 255));
}
