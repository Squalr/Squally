#include "SantaHatPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SantaHatPlans::SaveKey = "santa-hat-plans";

SantaHatPlans* SantaHatPlans::create()
{
	SantaHatPlans* instance = new SantaHatPlans();

	instance->autorelease();

	return instance;
}

SantaHatPlans::SantaHatPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SantaHatPlans::~SantaHatPlans()
{
}

std::vector<Item*> SantaHatPlans::craft()
{
	return { SantaHat::create() };
}

std::vector<std::tuple<Item*, int>> SantaHatPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* SantaHatPlans::clone()
{
	return SantaHatPlans::create();
}

LocalizedString* SantaHatPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

const std::string& SantaHatPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SantaHatPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_SantaHat;
}

const std::string& SantaHatPlans::getIdentifier()
{
	return SantaHatPlans::SaveKey;
}
