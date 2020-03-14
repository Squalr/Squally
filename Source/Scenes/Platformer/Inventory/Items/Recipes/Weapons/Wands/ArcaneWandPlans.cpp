#include "ArcaneWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ArcaneWandPlans::SaveKeyArcaneWandPlans = "arcane-wand-plans";

ArcaneWandPlans* ArcaneWandPlans::create()
{
	ArcaneWandPlans* instance = new ArcaneWandPlans();

	instance->autorelease();

	return instance;
}

ArcaneWandPlans::ArcaneWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

ArcaneWandPlans::~ArcaneWandPlans()
{
}

Item* ArcaneWandPlans::craft()
{
	return ArcaneWand::create();
}

std::vector<std::tuple<Item*, int>> ArcaneWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
		{ Silver::create(), 2 },
		{ Gold::create(), 4 },
		{ Emerald::create(), 2 },
		{ Jade::create(), 3 },
	};
}

Item* ArcaneWandPlans::clone()
{
	return ArcaneWandPlans::create();
}

std::string ArcaneWandPlans::getItemName()
{
	return ArcaneWandPlans::SaveKeyArcaneWandPlans;
}

LocalizedString* ArcaneWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_ArcaneWand::create();
}

std::string ArcaneWandPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string ArcaneWandPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_ArcaneWand;
}

std::string ArcaneWandPlans::getSerializationKey()
{
	return ArcaneWandPlans::SaveKeyArcaneWandPlans;
}
