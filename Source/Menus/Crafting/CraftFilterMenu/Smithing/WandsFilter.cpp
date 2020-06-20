#include "WandsFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/WandRecipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

WandsFilter* WandsFilter::create()
{
	WandsFilter* itemPreview = new WandsFilter();

	itemPreview->autorelease();

	return itemPreview;
}

WandsFilter::WandsFilter() : super (Strings::Menus_Crafting_Wands::create(), UIResources::Menus_CraftingMenu_WandIcon)
{
}

WandsFilter::~WandsFilter()
{
}

void WandsFilter::onEnter()
{
	super::onEnter();
}

void WandsFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> WandsFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<WandRecipe*>(item) == nullptr;
	}), itemList.end());

	return itemList;
}
