#include "ManaWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ManaWandPlans::SaveKeyManaWandPlans = "mana-wand-plans";

ManaWandPlans* ManaWandPlans::create()
{
	ManaWandPlans* instance = new ManaWandPlans();

	instance->autorelease();

	return instance;
}

ManaWandPlans::ManaWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

ManaWandPlans::~ManaWandPlans()
{
}

Item* ManaWandPlans::craft()
{
	return ManaWand::create();
}

std::vector<std::tuple<Item*, int>> ManaWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* ManaWandPlans::clone()
{
	return ManaWandPlans::create();
}

std::string ManaWandPlans::getItemName()
{
	return ManaWandPlans::SaveKeyManaWandPlans;
}

LocalizedString* ManaWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_ManaWand::create();
}

std::string ManaWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string ManaWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_ManaWand;
}

std::string ManaWandPlans::getSerializationKey()
{
	return ManaWandPlans::SaveKeyManaWandPlans;
}
