#include "AllFilter.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Inventory/All.h"

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
	return itemList;
}
