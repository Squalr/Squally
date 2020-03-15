#include "BlacksmithingMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterMenu.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/AllWeaponsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/AxesFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/BowsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/MacesFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/SpearsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/SwordsFilter.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

BlacksmithingMenu* BlacksmithingMenu::create()
{
	BlacksmithingMenu* instance = new BlacksmithingMenu();

	instance->autorelease();

	return instance;
}

BlacksmithingMenu::BlacksmithingMenu()
{
	this->anvil = Sprite::create(UIResources::Menus_CraftingMenu_Anvil);
	this->craftButton = ClickableNode::create(UIResources::Menus_CraftingMenu_CraftButton, UIResources::Menus_CraftingMenu_CraftButtonSelected);
	this->craftButtonDisabled = Sprite::create(UIResources::Menus_CraftingMenu_CraftButton);

	this->filterMenu->addFilter(AllWeaponsFilter::create());
	this->filterMenu->addFilter(AxesFilter::create());
	this->filterMenu->addFilter(BowsFilter::create());
	this->filterMenu->addFilter(MacesFilter::create());
	this->filterMenu->addFilter(SpearsFilter::create());
	this->filterMenu->addFilter(SwordsFilter::create());

	this->backDecorNode->addChild(this->anvil);
	this->addChild(this->craftButton);
	this->addChild(this->craftButtonDisabled);
}

BlacksmithingMenu::~BlacksmithingMenu()
{
}

void BlacksmithingMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const Vec2 AnvilOffset = Vec2(-72.0f, 0.0f);

	this->anvil->setPosition(Vec2(visibleSize.width / 2.0f + 359.0f, visibleSize.height / 2.0f + 54.0f) + AnvilOffset);
	this->craftButton->setPosition(Vec2(visibleSize.width / 2.0f + 456.0f, visibleSize.height / 2.0f - 288.0f));
	this->craftButtonDisabled->setPosition(this->craftButton->getPosition());
}

void BlacksmithingMenu::initializeListeners()
{
	super::initializeListeners();

	this->craftButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->tryCraftItem();
	});
}

void BlacksmithingMenu::onCraftPreview(Item* item)
{
	super::onCraftPreview(item);
	
	if (this->canCraft)
	{
		this->craftButton->enableInteraction();
		this->craftButton->setVisible(true);
		this->craftButtonDisabled->setVisible(false);
	}
	else
	{
		this->craftButton->disableInteraction();
		this->craftButton->setVisible(false);
		this->craftButtonDisabled->setVisible(true);
	}
}
