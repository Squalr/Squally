#include "DismantleMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Sound/Sound.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"
#include "Menus/Crafting/CraftFilterMenu/CraftFilterMenu.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/AllWeaponsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/AxesFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/BowsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/MacesFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/SwordsFilter.h"
#include "Menus/Crafting/CraftFilterMenu/Smithing/WandsFilter.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DismantleMenu* DismantleMenu::create()
{
	DismantleMenu* instance = new DismantleMenu();

	instance->autorelease();

	return instance;
}

DismantleMenu::DismantleMenu()
{
	this->anvil = Sprite::create(UIResources::Menus_CraftingMenu_Anvil);
	this->icon = Sprite::create(UIResources::Menus_CraftingMenu_AnvilIcon);
	this->craftSound = Sound::create(SoundResources::Menus_Crafting_Blacksmithing);

	this->filterMenu->addFilter(AllWeaponsFilter::create());
	this->filterMenu->addFilter(AxesFilter::create());
	this->filterMenu->addFilter(BowsFilter::create());
	this->filterMenu->addFilter(MacesFilter::create());
	this->filterMenu->addFilter(SwordsFilter::create());
	this->filterMenu->addFilter(WandsFilter::create());

	this->backDecorNode->addChild(this->anvil);
	this->craftIconNode->addChild(this->icon);
	this->addChild(this->craftSound);
}

DismantleMenu::~DismantleMenu()
{
}

void DismantleMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const Vec2 AnvilOffset = Vec2(-72.0f, 0.0f);

	this->anvil->setPosition(Vec2(visibleSize.width / 2.0f + 359.0f, visibleSize.height / 2.0f + 54.0f) + AnvilOffset);
}

void DismantleMenu::onCraftStart()
{
	this->craftSound->stop();
	this->craftSound->play();
}

void DismantleMenu::onCraftEnd(bool viaCancel)
{
	if (viaCancel)
	{
		this->craftSound->stop();
	}
}
