#include "RoyalCrownPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RoyalCrownPlans::SaveKey = "royal-crown-plans";

RoyalCrownPlans* RoyalCrownPlans::create()
{
	RoyalCrownPlans* instance = new RoyalCrownPlans();

	instance->autorelease();

	return instance;
}

RoyalCrownPlans::RoyalCrownPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

RoyalCrownPlans::~RoyalCrownPlans()
{
}

std::vector<Item*> RoyalCrownPlans::craft()
{
	return { RoyalCrown::create() };
}

std::vector<std::tuple<Item*, int>> RoyalCrownPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* RoyalCrownPlans::clone()
{
	return RoyalCrownPlans::create();
}

LocalizedString* RoyalCrownPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_RoyalCrown::create();
}

const std::string& RoyalCrownPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string RoyalCrownPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Special_RoyalCrown;
}

const std::string& RoyalCrownPlans::getIdentifier()
{
	return RoyalCrownPlans::SaveKey;
}
