#include "PriestHatPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PriestHatPlans::SaveKey = "priest-hat-plans";

PriestHatPlans* PriestHatPlans::create()
{
	PriestHatPlans* instance = new PriestHatPlans();

	instance->autorelease();

	return instance;
}

PriestHatPlans::PriestHatPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

PriestHatPlans::~PriestHatPlans()
{
}

std::vector<Item*> PriestHatPlans::craft()
{
	return { PriestHat::create() };
}

std::vector<std::tuple<Item*, int>> PriestHatPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* PriestHatPlans::clone()
{
	return PriestHatPlans::create();
}

LocalizedString* PriestHatPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_PriestHat::create();
}

const std::string& PriestHatPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string PriestHatPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_PriestHat;
}

const std::string& PriestHatPlans::getIdentifier()
{
	return PriestHatPlans::SaveKey;
}
