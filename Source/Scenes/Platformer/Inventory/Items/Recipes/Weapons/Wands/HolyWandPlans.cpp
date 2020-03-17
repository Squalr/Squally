#include "HolyWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HolyWandPlans::SaveKeyHolyWandPlans = "holy-wand-plans";

HolyWandPlans* HolyWandPlans::create()
{
	HolyWandPlans* instance = new HolyWandPlans();

	instance->autorelease();

	return instance;
}

HolyWandPlans::HolyWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

HolyWandPlans::~HolyWandPlans()
{
}

Item* HolyWandPlans::craft()
{
	return HolyWand::create();
}

std::vector<std::tuple<Item*, int>> HolyWandPlans::getReagentsInternal()
{
	return
	{
		{ Silver::create(), 2 },
		{ Gold::create(), 8 },
		{ Sulfur::create(), 4 },
		{ Diamond::create(), 1 },
	};
}

Item* HolyWandPlans::clone()
{
	return HolyWandPlans::create();
}

std::string HolyWandPlans::getItemName()
{
	return HolyWandPlans::SaveKeyHolyWandPlans;
}

LocalizedString* HolyWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_HolyWand::create();
}

std::string HolyWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string HolyWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_HolyWand;
}

std::string HolyWandPlans::getSerializationKey()
{
	return HolyWandPlans::SaveKeyHolyWandPlans;
}
