#include "MagesHatBluePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MagesHatBluePlans::SaveKey = "mages-hat-blue-plans";

MagesHatBluePlans* MagesHatBluePlans::create()
{
	MagesHatBluePlans* instance = new MagesHatBluePlans();

	instance->autorelease();

	return instance;
}

MagesHatBluePlans::MagesHatBluePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

MagesHatBluePlans::~MagesHatBluePlans()
{
}

std::vector<Item*> MagesHatBluePlans::craft()
{
	return { MagesHatBlue::create() };
}

std::vector<std::tuple<Item*, int>> MagesHatBluePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* MagesHatBluePlans::clone()
{
	return MagesHatBluePlans::create();
}

LocalizedString* MagesHatBluePlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_MagesHatBlue::create();
}

const std::string& MagesHatBluePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string MagesHatBluePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_MagesHatBlue;
}

const std::string& MagesHatBluePlans::getIdentifier()
{
	return MagesHatBluePlans::SaveKey;
}
