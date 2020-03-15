#include "BowsFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/BowRecipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

BowsFilter* BowsFilter::create()
{
	BowsFilter* itemPreview = new BowsFilter();

	itemPreview->autorelease();

	return itemPreview;
}

BowsFilter::BowsFilter() : super (Strings::Menus_Crafting_Bows::create(), UIResources::Menus_CraftingMenu_BowIcon)
{
}

BowsFilter::~BowsFilter()
{
}

void BowsFilter::onEnter()
{
	super::onEnter();
}

void BowsFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> BowsFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<BowRecipe*>(item) == nullptr;
	}), itemList.end());

	return itemList;
}
