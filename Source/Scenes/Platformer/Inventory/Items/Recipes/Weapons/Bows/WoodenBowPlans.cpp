#include "WoodenBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenBowPlans::SaveKey = "wooden-bow-plans";

WoodenBowPlans* WoodenBowPlans::create()
{
	WoodenBowPlans* instance = new WoodenBowPlans();

	instance->autorelease();

	return instance;
}

WoodenBowPlans::WoodenBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WoodenBowPlans::~WoodenBowPlans()
{
}

Item* WoodenBowPlans::craft()
{
	return WoodenBow::create();
}

std::vector<std::tuple<Item*, int>> WoodenBowPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
		{ Feather::create(), 10 },
	};
}

Item* WoodenBowPlans::clone()
{
	return WoodenBowPlans::create();
}

std::string WoodenBowPlans::getItemName()
{
	return WoodenBowPlans::SaveKey;
}

LocalizedString* WoodenBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_WoodenBow::create();
}

std::string WoodenBowPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WoodenBowPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_WoodenBow;
}

std::string WoodenBowPlans::getSerializationKey()
{
	return WoodenBowPlans::SaveKey;
}
