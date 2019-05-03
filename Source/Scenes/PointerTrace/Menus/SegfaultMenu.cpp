#include "SegfaultMenu.h"

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
#include "Events/NavigationEvents.h"

#include "Resources/PointerTraceResources.h"
#include "Resources/UIResources.h"

#include "Strings/PointerTrace/Segfault.h"
#include "Strings/Menus/Retry.h"
#include "Strings/Menus/Leave.h"

using namespace cocos2d;

SegfaultMenu* SegfaultMenu::create()
{
	SegfaultMenu* instance = new SegfaultMenu();

	instance->autorelease();

	return instance;
}

SegfaultMenu::SegfaultMenu()
{
	this->segfaultMenu = Sprite::create(PointerTraceResources::SegfaultMenu);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::PointerTrace_Segfault::create());
	
	LocalizedLabel*	retryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Retry::create());
	LocalizedLabel*	retryLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Retry::create());

	this->retryButton = ClickableTextNode::create(retryLabel, retryLabelHover, Sprite::create(UIResources::Menus_Buttons_GenericButton), Sprite::create(UIResources::Menus_Buttons_GenericButtonHover));

	LocalizedLabel*	leaveLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Leave::create());
	LocalizedLabel*	leaveLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Leave::create());

	this->leaveButton = ClickableTextNode::create(leaveLabel, leaveLabelHover, Sprite::create(UIResources::Menus_Buttons_GenericButton), Sprite::create(UIResources::Menus_Buttons_GenericButtonHover));

	this->titleLabel->enableOutline(Color4B::BLACK, 2);
	retryLabel->enableOutline(Color4B::BLACK, 2);
	retryLabelHover->enableOutline(Color4B::BLACK, 2);
	leaveLabel->enableOutline(Color4B::BLACK, 2);
	leaveLabelHover->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->segfaultMenu);
	this->addChild(this->titleLabel);
	this->addChild(this->retryButton);
	this->addChild(this->leaveButton);
}

void SegfaultMenu::onEnter()
{
	super::onEnter();

	this->setVisible(false);

	this->scheduleUpdate();
}

void SegfaultMenu::initializePositions()
{
	super::initializePositions();

	this->titleLabel->setPositionY(224.0f);
	this->leaveButton->setPositionY(-48.0f + -64.0f);
	this->retryButton->setPositionY(-48.0f + 64.0f);
}

void SegfaultMenu::initializeListeners()
{
	super::initializeListeners();

	this->leaveButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*) { NavigationEvents::navigateTitle(); } );
}

void SegfaultMenu::setMapResource(std::string mapResource)
{
	this->retryButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		NavigationEvents::navigatePointerTraceMap(mapResource);
	});
}
