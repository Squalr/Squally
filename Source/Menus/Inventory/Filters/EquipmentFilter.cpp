#include "EquipmentFilter.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Inventory/Equipment.h"

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
	return itemList;
}
