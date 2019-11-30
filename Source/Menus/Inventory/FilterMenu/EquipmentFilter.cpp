#include "EquipmentFilter.h"

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

EquipmentFilter* EquipmentFilter::create()
{
	EquipmentFilter* itemPreview = new EquipmentFilter();

	itemPreview->autorelease();

	return itemPreview;
}

EquipmentFilter::EquipmentFilter() : super (Strings::Menus_Inventory_Equipment::create(), UIResources::Menus_InventoryMenu_EquipmentIcon)
{
}

EquipmentFilter::~EquipmentFilter()
{
}

void EquipmentFilter::onEnter()
{
	super::onEnter();
}

void EquipmentFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> EquipmentFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		if (dynamic_cast<HexusCard*>(item) != nullptr)
		{
			return true;
		}

		if (dynamic_cast<Equipable*>(item) != nullptr)
		{
			return false;
		}

		return true; 
	}), itemList.end());

	return itemList;
}
