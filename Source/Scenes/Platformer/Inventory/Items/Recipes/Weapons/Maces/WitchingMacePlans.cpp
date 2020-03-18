#include "WitchingMacePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WitchingMacePlans::SaveKeyWitchingMacePlans = "witching-mace-plans";

WitchingMacePlans* WitchingMacePlans::create()
{
	WitchingMacePlans* instance = new WitchingMacePlans();

	instance->autorelease();

	return instance;
}

WitchingMacePlans::WitchingMacePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WitchingMacePlans::~WitchingMacePlans()
{
}

Item* WitchingMacePlans::craft()
{
	return SpikedClub::create();
}

std::vector<std::tuple<Item*, int>> WitchingMacePlans::getReagentsInternal()
{
	return
	{
		{ Copper::create(), 3 },
		{ LightWood::create(), 10 },
		{ Iron::create(), 2 },
	};
}

Item* WitchingMacePlans::clone()
{
	return WitchingMacePlans::create();
}

std::string WitchingMacePlans::getItemName()
{
	return WitchingMacePlans::SaveKeyWitchingMacePlans;
}

LocalizedString* WitchingMacePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_SpikedClub::create();
}

std::string WitchingMacePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WitchingMacePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_SpikedClub;
}

std::string WitchingMacePlans::getSerializationKey()
{
	return WitchingMacePlans::SaveKeyWitchingMacePlans;
}
