#include "AllEquipmentFilter.h"

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

AllEquipmentFilter* AllEquipmentFilter::create()
{
	AllEquipmentFilter* itemPreview = new AllEquipmentFilter();

	itemPreview->autorelease();

	return itemPreview;
}

AllEquipmentFilter::AllEquipmentFilter() : super (Strings::Menus_Crafting_All::create(), UIResources::Menus_CraftingMenu_AllIcon)
{
}

AllEquipmentFilter::~AllEquipmentFilter()
{
}

void AllEquipmentFilter::onEnter()
{
	super::onEnter();
}

void AllEquipmentFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> AllEquipmentFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<Recipe*>(item) == nullptr; 
	}), itemList.end());

	return itemList;
}
