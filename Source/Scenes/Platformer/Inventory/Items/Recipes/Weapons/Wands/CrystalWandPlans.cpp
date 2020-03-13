#include "CrystalWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalWandPlans::SaveKeyCrystalWandPlans = "crystal-wand-plans";

CrystalWandPlans* CrystalWandPlans::create()
{
	CrystalWandPlans* instance = new CrystalWandPlans();

	instance->autorelease();

	return instance;
}

CrystalWandPlans::CrystalWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CrystalWandPlans::~CrystalWandPlans()
{
}

Item* CrystalWandPlans::craft()
{
	return CrystalWand::create();
}

std::map<Item*, int> CrystalWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* CrystalWandPlans::clone()
{
	return CrystalWandPlans::create();
}

std::string CrystalWandPlans::getItemName()
{
	return CrystalWandPlans::SaveKeyCrystalWandPlans;
}

LocalizedString* CrystalWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_CrystalWand::create();
}

std::string CrystalWandPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string CrystalWandPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_CrystalWand;
}

std::string CrystalWandPlans::getSerializationKey()
{
	return CrystalWandPlans::SaveKeyCrystalWandPlans;
}
