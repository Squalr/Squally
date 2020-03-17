#include "HedgeTrimmerPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HedgeTrimmerPlans::SaveKeyHedgeTrimmerPlans = "hedge-splitter-plans";

HedgeTrimmerPlans* HedgeTrimmerPlans::create()
{
	HedgeTrimmerPlans* instance = new HedgeTrimmerPlans();

	instance->autorelease();

	return instance;
}

HedgeTrimmerPlans::HedgeTrimmerPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

HedgeTrimmerPlans::~HedgeTrimmerPlans()
{
}

Item* HedgeTrimmerPlans::craft()
{
	return HedgeTrimmer::create();
}

std::vector<std::tuple<Item*, int>> HedgeTrimmerPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* HedgeTrimmerPlans::clone()
{
	return HedgeTrimmerPlans::create();
}

std::string HedgeTrimmerPlans::getItemName()
{
	return HedgeTrimmerPlans::SaveKeyHedgeTrimmerPlans;
}

LocalizedString* HedgeTrimmerPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_HedgeTrimmer::create();
}

std::string HedgeTrimmerPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string HedgeTrimmerPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_HedgeTrimmer;
}

std::string HedgeTrimmerPlans::getSerializationKey()
{
	return HedgeTrimmerPlans::SaveKeyHedgeTrimmerPlans;
}
