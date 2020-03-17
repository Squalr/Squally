#include "EnchantedWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EnchantedWandPlans::SaveKeyEnchantedWandPlans = "enchanted-wand-plans";

EnchantedWandPlans* EnchantedWandPlans::create()
{
	EnchantedWandPlans* instance = new EnchantedWandPlans();

	instance->autorelease();

	return instance;
}

EnchantedWandPlans::EnchantedWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

EnchantedWandPlans::~EnchantedWandPlans()
{
}

Item* EnchantedWandPlans::craft()
{
	return EnchantedWand::create();
}

std::vector<std::tuple<Item*, int>> EnchantedWandPlans::getReagentsInternal()
{
	return
	{
		{ LightWood::create(), 6 },
		{ Emerald::create(), 1 },
	};
}

Item* EnchantedWandPlans::clone()
{
	return EnchantedWandPlans::create();
}

std::string EnchantedWandPlans::getItemName()
{
	return EnchantedWandPlans::SaveKeyEnchantedWandPlans;
}

LocalizedString* EnchantedWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_EnchantedWand::create();
}

std::string EnchantedWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string EnchantedWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_EnchantedWand;
}

std::string EnchantedWandPlans::getSerializationKey()
{
	return EnchantedWandPlans::SaveKeyEnchantedWandPlans;
}
