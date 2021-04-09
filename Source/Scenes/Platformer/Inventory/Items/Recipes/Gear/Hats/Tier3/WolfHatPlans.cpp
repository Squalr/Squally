#include "WolfHatPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WolfHatPlans::SaveKey = "wolf-hat-plans";

WolfHatPlans* WolfHatPlans::create()
{
	WolfHatPlans* instance = new WolfHatPlans();

	instance->autorelease();

	return instance;
}

WolfHatPlans::WolfHatPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WolfHatPlans::~WolfHatPlans()
{
}

std::vector<Item*> WolfHatPlans::craft()
{
	return { WolfHat::create() };
}

std::vector<std::tuple<Item*, int>> WolfHatPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WolfHatPlans::clone()
{
	return WolfHatPlans::create();
}

LocalizedString* WolfHatPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WolfHat::create();
}

const std::string& WolfHatPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WolfHatPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WolfHat;
}

const std::string& WolfHatPlans::getIdentifier()
{
	return WolfHatPlans::SaveKey;
}
