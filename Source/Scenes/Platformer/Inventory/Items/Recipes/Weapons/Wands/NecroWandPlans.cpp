#include "NecroWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string NecroWandPlans::SaveKeyNecroWandPlans = "necro-wand-plans";

NecroWandPlans* NecroWandPlans::create()
{
	NecroWandPlans* instance = new NecroWandPlans();

	instance->autorelease();

	return instance;
}

NecroWandPlans::NecroWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

NecroWandPlans::~NecroWandPlans()
{
}

Item* NecroWandPlans::craft()
{
	return NecroWand::create();
}

std::map<Item*, int> NecroWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* NecroWandPlans::clone()
{
	return NecroWandPlans::create();
}

std::string NecroWandPlans::getItemName()
{
	return NecroWandPlans::SaveKeyNecroWandPlans;
}

LocalizedString* NecroWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_NecroWand::create();
}

std::string NecroWandPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string NecroWandPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_NecroWand;
}

std::string NecroWandPlans::getSerializationKey()
{
	return NecroWandPlans::SaveKeyNecroWandPlans;
}
