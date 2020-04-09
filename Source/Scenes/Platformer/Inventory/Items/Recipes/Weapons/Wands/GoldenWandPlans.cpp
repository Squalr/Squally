#include "GoldenWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenWandPlans::SaveKey = "golden-wand-plans";

GoldenWandPlans* GoldenWandPlans::create()
{
	GoldenWandPlans* instance = new GoldenWandPlans();

	instance->autorelease();

	return instance;
}

GoldenWandPlans::GoldenWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GoldenWandPlans::~GoldenWandPlans()
{
}

Item* GoldenWandPlans::craft()
{
	return GoldenWand::create();
}

std::vector<std::tuple<Item*, int>> GoldenWandPlans::getReagentsInternal()
{
	return
	{
		{ Tin::create(), 2 },
		{ Gold::create(), 8 },
		{ Sulfur::create(), 4 },
		{ Diamond::create(), 1 },
	};
}

Item* GoldenWandPlans::clone()
{
	return GoldenWandPlans::create();
}

std::string GoldenWandPlans::getItemName()
{
	return GoldenWandPlans::SaveKey;
}

LocalizedString* GoldenWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_GoldenWand::create();
}

std::string GoldenWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GoldenWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_GoldenWand;
}

std::string GoldenWandPlans::getSerializationKey()
{
	return GoldenWandPlans::SaveKey;
}
