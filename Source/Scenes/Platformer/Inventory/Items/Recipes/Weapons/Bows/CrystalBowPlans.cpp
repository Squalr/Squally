#include "CrystalBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalBowPlans::SaveKeyCrystalBowPlans = "crystal-bow-plans";

CrystalBowPlans* CrystalBowPlans::create()
{
	CrystalBowPlans* instance = new CrystalBowPlans();

	instance->autorelease();

	return instance;
}

CrystalBowPlans::CrystalBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CrystalBowPlans::~CrystalBowPlans()
{
}

Item* CrystalBowPlans::craft()
{
	return CrystalBow::create();
}

std::vector<std::tuple<Item*, int>> CrystalBowPlans::getReagentsInternal()
{
	return
	{
		{ LightWood::create(), 8 },
		{ Iron::create(), 2 },
	};
}

Item* CrystalBowPlans::clone()
{
	return CrystalBowPlans::create();
}

std::string CrystalBowPlans::getItemName()
{
	return CrystalBowPlans::SaveKeyCrystalBowPlans;
}

LocalizedString* CrystalBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_CrystalBow::create();
}

std::string CrystalBowPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string CrystalBowPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_CrystalBow;
}

std::string CrystalBowPlans::getSerializationKey()
{
	return CrystalBowPlans::SaveKeyCrystalBowPlans;
}
