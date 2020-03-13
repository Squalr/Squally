#include "HolyWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

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

std::map<Item*, int> HolyWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
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
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string HolyWandPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_HolyWand;
}

std::string HolyWandPlans::getSerializationKey()
{
	return HolyWandPlans::SaveKeyHolyWandPlans;
}
