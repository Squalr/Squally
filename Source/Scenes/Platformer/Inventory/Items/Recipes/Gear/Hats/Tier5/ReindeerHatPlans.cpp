#include "ReindeerHatPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ReindeerHatPlans::SaveKey = "reindeer-hat-plans";

ReindeerHatPlans* ReindeerHatPlans::create()
{
	ReindeerHatPlans* instance = new ReindeerHatPlans();

	instance->autorelease();

	return instance;
}

ReindeerHatPlans::ReindeerHatPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

ReindeerHatPlans::~ReindeerHatPlans()
{
}

std::vector<Item*> ReindeerHatPlans::craft()
{
	return { ReindeerHat::create() };
}

std::vector<std::tuple<Item*, int>> ReindeerHatPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* ReindeerHatPlans::clone()
{
	return ReindeerHatPlans::create();
}

LocalizedString* ReindeerHatPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_ReindeerHat::create();
}

const std::string& ReindeerHatPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string ReindeerHatPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_ReindeerHat;
}

const std::string& ReindeerHatPlans::getIdentifier()
{
	return ReindeerHatPlans::SaveKey;
}
