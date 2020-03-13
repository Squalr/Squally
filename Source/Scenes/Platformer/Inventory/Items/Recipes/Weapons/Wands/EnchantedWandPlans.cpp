#include "EnchantedWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

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

std::map<Item*, int> EnchantedWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
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
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string EnchantedWandPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_EnchantedWand;
}

std::string EnchantedWandPlans::getSerializationKey()
{
	return EnchantedWandPlans::SaveKeyEnchantedWandPlans;
}
