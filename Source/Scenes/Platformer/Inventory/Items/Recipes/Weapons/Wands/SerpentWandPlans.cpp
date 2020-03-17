#include "SerpentWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SerpentWandPlans::SaveKeySerpentWandPlans = "serpent-wand-plans";

SerpentWandPlans* SerpentWandPlans::create()
{
	SerpentWandPlans* instance = new SerpentWandPlans();

	instance->autorelease();

	return instance;
}

SerpentWandPlans::SerpentWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SerpentWandPlans::~SerpentWandPlans()
{
}

Item* SerpentWandPlans::craft()
{
	return SerpentWand::create();
}

std::vector<std::tuple<Item*, int>> SerpentWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
		{ Gold::create(), 1 },
		{ Emerald::create(), 1 },
		{ Ruby::create(), 1 },
	};
}

Item* SerpentWandPlans::clone()
{
	return SerpentWandPlans::create();
}

std::string SerpentWandPlans::getItemName()
{
	return SerpentWandPlans::SaveKeySerpentWandPlans;
}

LocalizedString* SerpentWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_SerpentWand::create();
}

std::string SerpentWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SerpentWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_SerpentWand;
}

std::string SerpentWandPlans::getSerializationKey()
{
	return SerpentWandPlans::SaveKeySerpentWandPlans;
}
