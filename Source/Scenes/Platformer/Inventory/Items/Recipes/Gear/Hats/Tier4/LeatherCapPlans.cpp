#include "LeatherCapPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LeatherCapPlans::SaveKey = "leather-cap-plans";

LeatherCapPlans* LeatherCapPlans::create()
{
	LeatherCapPlans* instance = new LeatherCapPlans();

	instance->autorelease();

	return instance;
}

LeatherCapPlans::LeatherCapPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

LeatherCapPlans::~LeatherCapPlans()
{
}

std::vector<Item*> LeatherCapPlans::craft()
{
	return { LeatherCap::create() };
}

std::vector<std::tuple<Item*, int>> LeatherCapPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* LeatherCapPlans::clone()
{
	return LeatherCapPlans::create();
}

LocalizedString* LeatherCapPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_LeatherCap::create();
}

const std::string& LeatherCapPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string LeatherCapPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_LeatherCap;
}

const std::string& LeatherCapPlans::getIdentifier()
{
	return LeatherCapPlans::SaveKey;
}
