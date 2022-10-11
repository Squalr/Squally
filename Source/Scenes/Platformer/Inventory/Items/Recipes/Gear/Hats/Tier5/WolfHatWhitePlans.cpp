#include "WolfHatWhitePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WolfHatWhitePlans::SaveKey = "wolf-hat-white-plans";

WolfHatWhitePlans* WolfHatWhitePlans::create()
{
	WolfHatWhitePlans* instance = new WolfHatWhitePlans();

	instance->autorelease();

	return instance;
}

WolfHatWhitePlans::WolfHatWhitePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WolfHatWhitePlans::~WolfHatWhitePlans()
{
}

std::vector<Item*> WolfHatWhitePlans::craft()
{
	return { WolfHatWhite::create() };
}

std::vector<std::tuple<Item*, int>> WolfHatWhitePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WolfHatWhitePlans::clone()
{
	return WolfHatWhitePlans::create();
}

LocalizedString* WolfHatWhitePlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WolfHatWhite::create();
}

const std::string& WolfHatWhitePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WolfHatWhitePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WolfHatWhite;
}

const std::string& WolfHatWhitePlans::getIdentifier()
{
	return WolfHatWhitePlans::SaveKey;
}
