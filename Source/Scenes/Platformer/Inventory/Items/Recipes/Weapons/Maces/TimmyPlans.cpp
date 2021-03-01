#include "TimmyPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TimmyPlans::SaveKey = "timmy-plans";

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

std::vector<Item*> TimmyPlans::craft()
{
	return { WitchingMace::create() };
}

std::vector<std::tuple<Item*, int>> TimmyPlans::getReagentsInternal()
{
	return
	{
		{ Copper::create(), 3 },
		{ Wood::create(), 10 },
		{ Iron::create(), 2 },
	};
}

Item* TimmyPlans::clone()
{
	return TimmyPlans::create();
}

std::string TimmyPlans::getItemName()
{
	return TimmyPlans::SaveKey;
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
	return TimmyPlans::SaveKey;
}
