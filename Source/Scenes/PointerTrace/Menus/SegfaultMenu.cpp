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
#include "Strings/Menus/QuitToTitle.h"

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

	LocalizedLabel*	quitToTitleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_QuitToTitle::create());
	LocalizedLabel*	quitToTitleLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_QuitToTitle::create());

	this->quitToTitleButton = ClickableTextNode::create(quitToTitleLabel, quitToTitleLabelHover, Sprite::create(UIResources::Menus_Buttons_GenericButton), Sprite::create(UIResources::Menus_Buttons_GenericButtonHover));

	this->titleLabel->enableOutline(Color4B::BLACK, 2);
	retryLabel->enableOutline(Color4B::BLACK, 2);
	retryLabelHover->enableOutline(Color4B::BLACK, 2);
	quitToTitleLabel->enableOutline(Color4B::BLACK, 2);
	quitToTitleLabelHover->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->segfaultMenu);
	this->addChild(this->titleLabel);
	this->addChild(this->retryButton);
	this->addChild(this->quitToTitleButton);
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
	this->quitToTitleButton->setPositionY(-48.0f + -64.0f);
	this->retryButton->setPositionY(-48.0f + 64.0f);
}

void SegfaultMenu::initializeListeners()
{
	super::initializeListeners();

	this->quitToTitleButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*) { NavigationEvents::navigateTitle(); } );
}

void SegfaultMenu::setRetryParams(std::string mapResource, std::function<void()> onLevelClearCallback)
{
	this->retryButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		NavigationEvents::navigatePointerTraceMap(NavigationEvents::NavigatePointerTraceMapArgs(mapResource, onLevelClearCallback));
	});
}
