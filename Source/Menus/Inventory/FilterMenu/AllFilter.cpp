#include "AllFilter.h"

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

AllFilter* AllFilter::create()
{
	AllFilter* itemPreview = new AllFilter();

	itemPreview->autorelease();

	return itemPreview;
}

AllFilter::AllFilter() : super (Strings::Menus_Inventory_All::create(), UIResources::Menus_InventoryMenu_AllIcon)
{
}

AllFilter::~AllFilter()
{
}

void AllFilter::onEnter()
{
	super::onEnter();
}

void AllFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> AllFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		if (dynamic_cast<HexusCard*>(item) != nullptr)
		{
			return true;
		}

		return false; 
	}), itemList.end());

	return itemList;
}
