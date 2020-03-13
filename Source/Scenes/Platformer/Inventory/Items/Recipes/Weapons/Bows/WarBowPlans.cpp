#include "WarBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

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

std::map<Item*, int> WarBowPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
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
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string WarBowPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_WarBow;
}

std::string WarBowPlans::getSerializationKey()
{
	return WarBowPlans::SaveKeyWarBowPlans;
}
