#include "AxesFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/AxeRecipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

AxesFilter* AxesFilter::create()
{
	AxesFilter* itemPreview = new AxesFilter();

	itemPreview->autorelease();

	return itemPreview;
}

AxesFilter::AxesFilter() : super (Strings::Menus_Inventory_Consumables::create(), UIResources::Menus_InventoryMenu_EquipmentIcon)
{
}

AxesFilter::~AxesFilter()
{
}

void AxesFilter::onEnter()
{
	super::onEnter();
}

void AxesFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> AxesFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<AxeRecipe*>(item) == nullptr;
	}), itemList.end());

	return itemList;
}
