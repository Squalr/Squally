#include "ArchersHatPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ArchersHatPlans::SaveKey = "archers-hat-plans";

ArchersHatPlans* ArchersHatPlans::create()
{
	ArchersHatPlans* instance = new ArchersHatPlans();

	instance->autorelease();

	return instance;
}

ArchersHatPlans::ArchersHatPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

ArchersHatPlans::~ArchersHatPlans()
{
}

std::vector<Item*> ArchersHatPlans::craft()
{
	return { ArchersHat::create() };
}

std::vector<std::tuple<Item*, int>> ArchersHatPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* ArchersHatPlans::clone()
{
	return ArchersHatPlans::create();
}

LocalizedString* ArchersHatPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_ArchersHat::create();
}

const std::string& ArchersHatPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string ArchersHatPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_ArchersHat;
}

const std::string& ArchersHatPlans::getIdentifier()
{
	return ArchersHatPlans::SaveKey;
}
