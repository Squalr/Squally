#include "HellCrystalPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HellCrystalPlans::SaveKey = "hell-crystal-plans";

HellCrystalPlans* HellCrystalPlans::create()
{
	HellCrystalPlans* instance = new HellCrystalPlans();

	instance->autorelease();

	return instance;
}

HellCrystalPlans::HellCrystalPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

HellCrystalPlans::~HellCrystalPlans()
{
}

std::vector<Item*> HellCrystalPlans::craft()
{
	return { HellKey::create() };
}

std::vector<std::tuple<Item*, int>> HellCrystalPlans::getReagentsInternal()
{
	return
	{
		{ HellGateCrystal::create(), 1 },
	};
}

Item* HellCrystalPlans::clone()
{
	return HellCrystalPlans::create();
}

LocalizedString* HellCrystalPlans::getString()
{
	return Strings::Items_Misc_Keys_HellKey::create();
}

const std::string& HellCrystalPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string HellCrystalPlans::getCraftedItemIconResource()
{
	return ItemResources::Keys_HellKey;
}

const std::string& HellCrystalPlans::getIdentifier()
{
	return HellCrystalPlans::SaveKey;
}
