#include "SwordsFilter.h"

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

SwordsFilter* SwordsFilter::create()
{
	SwordsFilter* itemPreview = new SwordsFilter();

	itemPreview->autorelease();

	return itemPreview;
}

SwordsFilter::SwordsFilter() : super (Strings::Menus_Inventory_Consumables::create(), UIResources::Menus_InventoryMenu_ConsumablesIcon)
{
}

SwordsFilter::~SwordsFilter()
{
}

void SwordsFilter::onEnter()
{
	super::onEnter();
}

void SwordsFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> SwordsFilter::filter(std::vector<Item*> itemList)
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
