#include "AcolytesCapPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AcolytesCapPlans::SaveKey = "acolytes-cap-plans";

AcolytesCapPlans* AcolytesCapPlans::create()
{
	AcolytesCapPlans* instance = new AcolytesCapPlans();

	instance->autorelease();

	return instance;
}

AcolytesCapPlans::AcolytesCapPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

AcolytesCapPlans::~AcolytesCapPlans()
{
}

std::vector<Item*> AcolytesCapPlans::craft()
{
	return { AcolytesCap::create() };
}

std::vector<std::tuple<Item*, int>> AcolytesCapPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* AcolytesCapPlans::clone()
{
	return AcolytesCapPlans::create();
}

LocalizedString* AcolytesCapPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_AcolytesCap::create();
}

const std::string& AcolytesCapPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string AcolytesCapPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_AcolytesCap;
}

const std::string& AcolytesCapPlans::getIdentifier()
{
	return AcolytesCapPlans::SaveKey;
}
