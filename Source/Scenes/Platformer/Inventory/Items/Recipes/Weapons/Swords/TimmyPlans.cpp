#include "TimmyPlansPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TimmyPlansPlans::SaveKeyTimmyPlansPlans = "timmy-plans";

TimmyPlansPlans* TimmyPlansPlans::create()
{
	TimmyPlansPlans* instance = new TimmyPlansPlans();

	instance->autorelease();

	return instance;
}

TimmyPlansPlans::TimmyPlansPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

TimmyPlansPlans::~TimmyPlansPlans()
{
}

Item* TimmyPlansPlans::craft()
{
	return TimmyPlans::create();
}

std::vector<std::tuple<Item*, int>> TimmyPlansPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 1 },
		{ Iron::create(), 10 },
	};
}

Item* TimmyPlansPlans::clone()
{
	return TimmyPlansPlans::create();
}

std::string TimmyPlansPlans::getItemName()
{
	return TimmyPlansPlans::SaveKeyTimmyPlansPlans;
}

LocalizedString* TimmyPlansPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_TimmyPlans::create();
}

std::string TimmyPlansPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string TimmyPlansPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_TimmyPlans;
}

std::string TimmyPlansPlans::getSerializationKey()
{
	return TimmyPlansPlans::SaveKeyTimmyPlansPlans;
}
