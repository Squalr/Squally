#include "TimmyPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TimmyPlans::SaveKeyTimmyPlans = "timmy-plans";

TimmyPlans* TimmyPlans::create()
{
	TimmyPlans* instance = new TimmyPlans();

	instance->autorelease();

	return instance;
}

TimmyPlans::TimmyPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

TimmyPlans::~TimmyPlans()
{
}

Item* TimmyPlans::craft()
{
	return Timmy::create();
}

std::vector<std::tuple<Item*, int>> TimmyPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 1 },
		{ Iron::create(), 10 },
	};
}

Item* TimmyPlans::clone()
{
	return TimmyPlans::create();
}

std::string TimmyPlans::getItemName()
{
	return TimmyPlans::SaveKeyTimmyPlans;
}

LocalizedString* TimmyPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_Timmy::create();
}

std::string TimmyPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string TimmyPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Special_Timmy;
}

std::string TimmyPlans::getSerializationKey()
{
	return TimmyPlans::SaveKeyTimmyPlans;
}
