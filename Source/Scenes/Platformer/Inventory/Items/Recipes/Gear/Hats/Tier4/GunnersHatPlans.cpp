#include "GunnersHatPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GunnersHatPlans::SaveKey = "gunners-hat-plans";

GunnersHatPlans* GunnersHatPlans::create()
{
	GunnersHatPlans* instance = new GunnersHatPlans();

	instance->autorelease();

	return instance;
}

GunnersHatPlans::GunnersHatPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GunnersHatPlans::~GunnersHatPlans()
{
}

std::vector<Item*> GunnersHatPlans::craft()
{
	return { GunnersHat::create() };
}

std::vector<std::tuple<Item*, int>> GunnersHatPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* GunnersHatPlans::clone()
{
	return GunnersHatPlans::create();
}

LocalizedString* GunnersHatPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_GunnersHat::create();
}

const std::string& GunnersHatPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GunnersHatPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_GunnersHat;
}

const std::string& GunnersHatPlans::getIdentifier()
{
	return GunnersHatPlans::SaveKey;
}
