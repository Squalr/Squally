#include "VictoryMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Events/CombatEvents.h"

#include "Resources/PointerTraceResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

VictoryMenu* VictoryMenu::create()
{
	VictoryMenu* instance = new VictoryMenu();

	instance->autorelease();

	return instance;
}

VictoryMenu::VictoryMenu()
{
	this->segfaultMenu = Sprite::create(PointerTraceResources::SegfaultMenu);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::PointerTrace_Victory::create());
	
	LocalizedLabel*	leaveLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Leave::create());
	LocalizedLabel*	leaveLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Leave::create());

	this->leaveButton = ClickableTextNode::create(leaveLabel, leaveLabelHover, Sprite::create(UIResources::Menus_Buttons_GenericButton), Sprite::create(UIResources::Menus_Buttons_GenericButtonHover));

	this->titleLabel->enableOutline(Color4B::BLACK, 2);
	leaveLabel->enableOutline(Color4B::BLACK, 2);
	leaveLabelHover->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->segfaultMenu);
	this->addChild(this->titleLabel);
	this->addChild(this->leaveButton);
}

void VictoryMenu::onEnter()
{
	super::onEnter();

	this->setVisible(false);

	this->scheduleUpdate();
}

void VictoryMenu::initializePositions()
{
	super::initializePositions();

	this->titleLabel->setPositionY(224.0f);
	this->leaveButton->setPositionY(-48.0f);
}

void VictoryMenu::initializeListeners()
{
	super::initializeListeners();

	// this->leaveButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*) { NavigationEvents::NavigateBack(); } );
}
