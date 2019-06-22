#include "RewardsMenu.h"

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

#include "Strings/Combat/ItemsFound.h"
#include "Strings/Combat/Rewards.h"
#include "Strings/Combat/Victory.h"
#include "Strings/Menus/Return.h"

using namespace cocos2d;

RewardsMenu* RewardsMenu::create()
{
	RewardsMenu* instance = new RewardsMenu();

	instance->autorelease();

	return instance;
}

RewardsMenu::RewardsMenu()
{
	this->victoryMenu = Sprite::create(UIResources::Combat_VictoryMenu);
	this->rewardsMenu = Sprite::create(UIResources::Combat_ItemsMenu);
	this->victoryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::M2, Strings::Combat_Victory::create());
	this->itemsFoundLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Combat_ItemsFound::create());
	
	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);

	this->returnButton = ClickableTextNode::create(returnLabel, returnLabelHover, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->victoryLabel->enableOutline(Color4B::BLACK, 2);
	this->itemsFoundLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->victoryMenu);
	this->addChild(this->rewardsMenu);
	this->addChild(this->victoryLabel);
	this->addChild(this->itemsFoundLabel);
	this->addChild(this->returnButton);
}

RewardsMenu::~RewardsMenu()
{
}

void RewardsMenu::onEnter()
{
	super::onEnter();

	this->setOpacity(0);
}

void RewardsMenu::initializePositions()
{
	super::initializePositions();

	this->victoryLabel->setPosition(Vec2(-380.0f, 176.0f));
	this->victoryMenu->setPosition(Vec2(-380.0f, 0.0f));
	this->returnButton->setPosition(Vec2(512.0f, -280.0f));
	this->rewardsMenu->setPosition(Vec2(512.0f, 0.0f));
	this->itemsFoundLabel->setPosition(Vec2(512.0f, 256.0f));
}

void RewardsMenu::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventGiveRewards, [=](EventCustom* args)
	{
		this->loadRewards();
	}));

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		CombatEvents::TriggerReturnToMap();
	});
}

void RewardsMenu::show()
{
	this->runAction(FadeTo::create(1.0f, 255));
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

			this->rewardsMenu->addChild(itemIcon);
		}
	}));
}
