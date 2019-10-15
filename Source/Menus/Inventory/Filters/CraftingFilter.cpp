#include "CraftingFilter.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

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
	return itemList;
}
