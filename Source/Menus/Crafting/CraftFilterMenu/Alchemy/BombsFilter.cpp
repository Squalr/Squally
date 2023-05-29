#include "BombsFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/BombRecipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

BombsFilter* BombsFilter::create()
{
	BombsFilter* itemPreview = new BombsFilter();

	itemPreview->autorelease();

	return itemPreview;
}

BombsFilter::BombsFilter() : super (Strings::Menus_Crafting_Bombs::create(), UIResources::Menus_CraftingMenu_BombIcon)
{
}

BombsFilter::~BombsFilter()
{
}

void BombsFilter::onEnter()
{
	super::onEnter();
}

void BombsFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> BombsFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<BombRecipe*>(item) == nullptr;
	}), itemList.end());

	return itemList;
}
