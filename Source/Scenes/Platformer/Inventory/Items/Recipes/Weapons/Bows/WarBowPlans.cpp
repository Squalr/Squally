#include "WarBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WarBowPlans::SaveKeyWarBowPlans = "war-bow-plans";

WarBowPlans* WarBowPlans::create()
{
	WarBowPlans* instance = new WarBowPlans();

	instance->autorelease();

	return instance;
}

WarBowPlans::WarBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WarBowPlans::~WarBowPlans()
{
}

Item* WarBowPlans::craft()
{
	return WarBow::create();
}

std::vector<std::tuple<Item*, int>> WarBowPlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 10 },
		{ Coal::create(), 8 },
		{ Silver::create(), 4 },
	};
}

Item* WarBowPlans::clone()
{
	return WarBowPlans::create();
}

std::string WarBowPlans::getItemName()
{
	return WarBowPlans::SaveKeyWarBowPlans;
}

LocalizedString* WarBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_WarBow::create();
}

std::string WarBowPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WarBowPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_WarBow;
}

std::string WarBowPlans::getSerializationKey()
{
	return WarBowPlans::SaveKeyWarBowPlans;
}
