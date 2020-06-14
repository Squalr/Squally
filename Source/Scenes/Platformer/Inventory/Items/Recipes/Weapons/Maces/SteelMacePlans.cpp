#include "SteelMacePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelMacePlans::SaveKey = "steel-mace-plans";

SteelMacePlans* SteelMacePlans::create()
{
	SteelMacePlans* instance = new SteelMacePlans();

	instance->autorelease();

	return instance;
}

SteelMacePlans::SteelMacePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SteelMacePlans::~SteelMacePlans()
{
}

Item* SteelMacePlans::craft()
{
	return SteelMace::create();
}

std::vector<std::tuple<Item*, int>> SteelMacePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 5 },
		{ Coal::create(), 4 },
		{ Iron::create(), 6 },
	};
}

Item* SteelMacePlans::clone()
{
	return SteelMacePlans::create();
}

std::string SteelMacePlans::getItemName()
{
	return SteelMacePlans::SaveKey;
}

LocalizedString* SteelMacePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_SteelMace::create();
}

std::string SteelMacePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SteelMacePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_SteelMace;
}

std::string SteelMacePlans::getSerializationKey()
{
	return SteelMacePlans::SaveKey;
}
