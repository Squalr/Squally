#include "WarlocksHeaddressPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WarlocksHeaddressPlans::SaveKey = "warlocks-headdress-plans";

WarlocksHeaddressPlans* WarlocksHeaddressPlans::create()
{
	WarlocksHeaddressPlans* instance = new WarlocksHeaddressPlans();

	instance->autorelease();

	return instance;
}

WarlocksHeaddressPlans::WarlocksHeaddressPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WarlocksHeaddressPlans::~WarlocksHeaddressPlans()
{
}

std::vector<Item*> WarlocksHeaddressPlans::craft()
{
	return { WarlocksHeaddress::create() };
}

std::vector<std::tuple<Item*, int>> WarlocksHeaddressPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WarlocksHeaddressPlans::clone()
{
	return WarlocksHeaddressPlans::create();
}

LocalizedString* WarlocksHeaddressPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WarlocksHeaddress::create();
}

const std::string& WarlocksHeaddressPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WarlocksHeaddressPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WarlocksHeaddress;
}

const std::string& WarlocksHeaddressPlans::getIdentifier()
{
	return WarlocksHeaddressPlans::SaveKey;
}
