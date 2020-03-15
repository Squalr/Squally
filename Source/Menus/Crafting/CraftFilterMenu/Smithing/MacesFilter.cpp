#include "MacesFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/MaceRecipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

MacesFilter* MacesFilter::create()
{
	MacesFilter* itemPreview = new MacesFilter();

	itemPreview->autorelease();

	return itemPreview;
}

MacesFilter::MacesFilter() : super (Strings::Menus_Crafting_Maces::create(), UIResources::Menus_CraftingMenu_MaceIcon)
{
}

MacesFilter::~MacesFilter()
{
}

void MacesFilter::onEnter()
{
	super::onEnter();
}

void MacesFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> MacesFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<MaceRecipe*>(item) == nullptr;
	}), itemList.end());

	return itemList;
}
