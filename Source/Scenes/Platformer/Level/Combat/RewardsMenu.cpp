#include "RewardsMenu.h"

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

#include "Strings/Combat/Rewards.h"
#include "Strings/Menus/Okay.h"

using namespace cocos2d;

RewardsMenu* RewardsMenu::create()
{
	RewardsMenu* instance = new RewardsMenu();

	instance->autorelease();

	return instance;
}

RewardsMenu::RewardsMenu()
{
	this->rewardsMenu = Sprite::create(UIResources::Combat_RewardsMenu);
	this->titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Combat_Rewards::create());
	this->rewardsScroll = ScrollPane::create(Size(480.0f, 640.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);

	LocalizedLabel*	okayLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Okay::create());
	LocalizedLabel*	okayLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Okay::create());

	this->okayButton = ClickableTextNode::create(okayLabel, okayLabelHover, Sprite::create(UIResources::Menus_Buttons_GenericButton), Sprite::create(UIResources::Menus_Buttons_GenericButtonHover));

	this->titleLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->rewardsMenu);
	this->addChild(this->titleLabel);
	this->addChild(this->rewardsScroll);
	this->addChild(this->okayButton);
}

void RewardsMenu::onEnter()
{
	super::onEnter();

	this->setVisible(false);

	this->scheduleUpdate();
}

void RewardsMenu::initializePositions()
{
	super::initializePositions();

	this->titleLabel->setPositionY(392.0f);
	this->okayButton->setPositionY(-392.0f);
}

void RewardsMenu::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventGiveRewards, [=](EventCustom* args)
	{
		this->loadRewards();
	}));

	this->okayButton->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
	{
		CombatEvents::TriggerReturnToMap();
	});
}

void RewardsMenu::update(float dt)
{
	super::update(dt);
}

void RewardsMenu::loadRewards()
{
	int index = 0;

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* entity)
	{
		std::vector<Item*> items = entity->getInventory()->getItems();

		for (auto it = items.begin(); it != items.end(); it++, index++)
		{
			ClickableNode* itemIcon = ClickableNode::create((*it)->getIconResource(), (*it)->getIconResource());
			int x = index % 3;
			int y = index / 3;

			itemIcon->setPosition(Vec2((x - 1) * 144.0f, y * -144.0f - 32.0f));

			this->rewardsScroll->addChild(itemIcon);
		}
	}));
}
