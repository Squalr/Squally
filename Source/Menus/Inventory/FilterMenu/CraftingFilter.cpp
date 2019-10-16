#include "CraftingFilter.h"

#include "Scenes/Platformer/Inventory/Items/Crafting/Crafting.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Inventory/Crafting.h"

using namespace cocos2d;

CraftingFilter* CraftingFilter::create()
{
	CraftingFilter* itemPreview = new CraftingFilter();

	itemPreview->autorelease();

	return itemPreview;
}

CraftingFilter::CraftingFilter() : super (Strings::Menus_Inventory_Crafting::create(), UIResources::Menus_InventoryMenu_CraftingIcon)
{
}

CraftingFilter::~CraftingFilter()
{
}

void CraftingFilter::onEnter()
{
	super::onEnter();
}

void CraftingFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> CraftingFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		if (dynamic_cast<Crafting*>(item) == nullptr)
		{
			return true;
		}

		return false; 
	}), itemList.end());

	return itemList;
}
