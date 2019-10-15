#include "ConsumablesFilter.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Inventory/Consumables.h"

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
	return itemList;
}
