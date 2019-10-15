#include "MiscFilter.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Inventory/Misc.h"

using namespace cocos2d;

MiscFilter* MiscFilter::create()
{
	MiscFilter* itemPreview = new MiscFilter();

	itemPreview->autorelease();

	return itemPreview;
}

MiscFilter::MiscFilter() : super (Strings::Menus_Inventory_Misc::create(), UIResources::Menus_InventoryMenu_MiscIcon)
{
}

MiscFilter::~MiscFilter()
{
}

void MiscFilter::onEnter()
{
	super::onEnter();
}

void MiscFilter::initializePositions()
{
	super::initializePositions();
}

std::vector<Item*> MiscFilter::filter(std::vector<Item*> itemList)
{
	return itemList;
}
