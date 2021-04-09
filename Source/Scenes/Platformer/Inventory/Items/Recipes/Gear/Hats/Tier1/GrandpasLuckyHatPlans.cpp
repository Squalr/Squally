#include "GrandpasLuckyHatPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GrandpasLuckyHatPlans::SaveKey = "grandpas-lucky-hat-plans";

GrandpasLuckyHatPlans* GrandpasLuckyHatPlans::create()
{
	GrandpasLuckyHatPlans* instance = new GrandpasLuckyHatPlans();

	instance->autorelease();

	return instance;
}

GrandpasLuckyHatPlans::GrandpasLuckyHatPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GrandpasLuckyHatPlans::~GrandpasLuckyHatPlans()
{
}

std::vector<Item*> GrandpasLuckyHatPlans::craft()
{
	return { GrandpasLuckyHat::create() };
}

std::vector<std::tuple<Item*, int>> GrandpasLuckyHatPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* GrandpasLuckyHatPlans::clone()
{
	return GrandpasLuckyHatPlans::create();
}

LocalizedString* GrandpasLuckyHatPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_GrandpasLuckyHat::create();
}

const std::string& GrandpasLuckyHatPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GrandpasLuckyHatPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_GrandpasLuckyHat;
}

const std::string& GrandpasLuckyHatPlans::getIdentifier()
{
	return GrandpasLuckyHatPlans::SaveKey;
}
