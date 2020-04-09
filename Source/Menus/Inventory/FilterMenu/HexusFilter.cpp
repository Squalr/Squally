#include "HexusFilter.h"

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

HexusFilter* HexusFilter::create()
{
	HexusFilter* itemPreview = new HexusFilter();

	itemPreview->autorelease();

	return itemPreview;
}

HexusFilter::HexusFilter() : super (Strings::Menus_Inventory_Equipment::create(), UIResources::Menus_InventoryMenu_HexusIcon)
{
}

HexusFilter::~HexusFilter()
{
}

void HexusFilter::onEnter()
{
	super::onEnter();
}

void HexusFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> HexusFilter::filter(std::vector<Item*> itemList)
{
	itemList.erase(std::remove_if(itemList.begin(), itemList.end(),
		[=](Item* item)
	{
		return dynamic_cast<HexusCard*>(item) == nullptr;
	}), itemList.end());

	return itemList;
}
