#include "PirateHatPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PirateHatPlans::SaveKey = "pirate-hat-plans";

PirateHatPlans* PirateHatPlans::create()
{
	PirateHatPlans* instance = new PirateHatPlans();

	instance->autorelease();

	return instance;
}

PirateHatPlans::PirateHatPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

PirateHatPlans::~PirateHatPlans()
{
}

std::vector<Item*> PirateHatPlans::craft()
{
	return { PirateHat::create() };
}

std::vector<std::tuple<Item*, int>> PirateHatPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* PirateHatPlans::clone()
{
	return PirateHatPlans::create();
}

LocalizedString* PirateHatPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_PirateHat::create();
}

const std::string& PirateHatPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string PirateHatPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_PirateHat;
}

const std::string& PirateHatPlans::getIdentifier()
{
	return PirateHatPlans::SaveKey;
}
