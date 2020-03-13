#include "WoodenWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenWandPlans::SaveKeyWoodenWandPlans = "wooden-wand-plans";

WoodenWandPlans* WoodenWandPlans::create()
{
	WoodenWandPlans* instance = new WoodenWandPlans();

	instance->autorelease();

	return instance;
}

WoodenWandPlans::WoodenWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WoodenWandPlans::~WoodenWandPlans()
{
}

Item* WoodenWandPlans::craft()
{
	return WoodenWand::create();
}

std::map<Item*, int> WoodenWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WoodenWandPlans::clone()
{
	return WoodenWandPlans::create();
}

std::string WoodenWandPlans::getItemName()
{
	return WoodenWandPlans::SaveKeyWoodenWandPlans;
}

LocalizedString* WoodenWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_WoodenWand::create();
}

std::string WoodenWandPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string WoodenWandPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_WoodenWand;
}

std::string WoodenWandPlans::getSerializationKey()
{
	return WoodenWandPlans::SaveKeyWoodenWandPlans;
}
