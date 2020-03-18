#include "WoodenRapierPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenRapierPlans::SaveKeyWoodenRapierPlans = "wooden-rapier-plans";

WoodenRapierPlans* WoodenRapierPlans::create()
{
	WoodenRapierPlans* instance = new WoodenRapierPlans();

	instance->autorelease();

	return instance;
}

WoodenRapierPlans::WoodenRapierPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WoodenRapierPlans::~WoodenRapierPlans()
{
}

Item* WoodenRapierPlans::craft()
{
	return WoodenRapier::create();
}

std::vector<std::tuple<Item*, int>> WoodenRapierPlans::getReagentsInternal()
{
	return
	{
		{ LightWood::create(), 2 },
		{ Iron::create(), 3 },
		{ Coal::create(), 3 },
		{ Gold::create(), 4 },
	};
}

Item* WoodenRapierPlans::clone()
{
	return WoodenRapierPlans::create();
}

std::string WoodenRapierPlans::getItemName()
{
	return WoodenRapierPlans::SaveKeyWoodenRapierPlans;
}

LocalizedString* WoodenRapierPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_WoodenRapier::create();
}

std::string WoodenRapierPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WoodenRapierPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_WoodenRapier;
}

std::string WoodenRapierPlans::getSerializationKey()
{
	return WoodenRapierPlans::SaveKeyWoodenRapierPlans;
}
