#include "ConsumablesFilter.h"

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ConsumablesFilter* ConsumablesFilter::create()
{
	ConsumablesFilter* itemPreview = new ConsumablesFilter();

	itemPreview->autorelease();

	return itemPreview;
}

ConsumablesFilter::ConsumablesFilter() : super (Strings::Menus_Inventory_Consumables::create(), UIResources::Menus_InventoryMenu_ConsumablesIcon)
{
}

ConsumablesFilter::~ConsumablesFilter()
{
}

void ConsumablesFilter::onEnter()
{
	super::onEnter();
}

void ConsumablesFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> ConsumablesFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		if (dynamic_cast<Consumable*>(item) != nullptr)
		{
			return false;
		}

		return true; 
	}), itemList.end());

	return itemList;
}
