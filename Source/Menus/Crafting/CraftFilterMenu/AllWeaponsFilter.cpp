#include "AllWeaponsFilter.h"

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

AllWeaponsFilter* AllWeaponsFilter::create()
{
	AllWeaponsFilter* itemPreview = new AllWeaponsFilter();

	itemPreview->autorelease();

	return itemPreview;
}

AllWeaponsFilter::AllWeaponsFilter() : super (Strings::Menus_Inventory_All::create(), UIResources::Menus_InventoryMenu_AllIcon)
{
}

AllWeaponsFilter::~AllWeaponsFilter()
{
}

void AllWeaponsFilter::onEnter()
{
	super::onEnter();
}

void AllWeaponsFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> AllWeaponsFilter::filter(std::vector<Item*> itemList)
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
