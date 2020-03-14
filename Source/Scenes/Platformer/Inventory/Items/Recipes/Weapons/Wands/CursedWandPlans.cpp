#include "CursedWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CursedWandPlans::SaveKeyCursedWandPlans = "cursed-wand-plans";

CursedWandPlans* CursedWandPlans::create()
{
	CursedWandPlans* instance = new CursedWandPlans();

	instance->autorelease();

	return instance;
}

CursedWandPlans::CursedWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CursedWandPlans::~CursedWandPlans()
{
}

Item* CursedWandPlans::craft()
{
	return CursedWand::create();
}

std::vector<std::tuple<Item*, int>> CursedWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
		{ Emerald::create(), 2 },
		{ Jade::create(), 1 },
	};
}

Item* CursedWandPlans::clone()
{
	return CursedWandPlans::create();
}

std::string CursedWandPlans::getItemName()
{
	return CursedWandPlans::SaveKeyCursedWandPlans;
}

LocalizedString* CursedWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_CursedWand::create();
}

std::string CursedWandPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string CursedWandPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_CursedWand;
}

std::string CursedWandPlans::getSerializationKey()
{
	return CursedWandPlans::SaveKeyCursedWandPlans;
}
