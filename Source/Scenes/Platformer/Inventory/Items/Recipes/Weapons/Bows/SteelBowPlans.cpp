#include "SteelBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelBowPlans::SaveKeySteelBowPlans = "steel-bow-plans";

SteelBowPlans* SteelBowPlans::create()
{
	SteelBowPlans* instance = new SteelBowPlans();

	instance->autorelease();

	return instance;
}

SteelBowPlans::SteelBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SteelBowPlans::~SteelBowPlans()
{
}

Item* SteelBowPlans::craft()
{
	return SteelBow::create();
}

std::vector<std::tuple<Item*, int>> SteelBowPlans::getReagentsInternal()
{
	return
	{
		{ LightWood::create(), 8 },
		{ Iron::create(), 4 },
		{ Coal::create(), 4 },
	};
}

Item* SteelBowPlans::clone()
{
	return SteelBowPlans::create();
}

std::string SteelBowPlans::getItemName()
{
	return SteelBowPlans::SaveKeySteelBowPlans;
}

LocalizedString* SteelBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_SteelBow::create();
}

std::string SteelBowPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SteelBowPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_SteelBow;
}

std::string SteelBowPlans::getSerializationKey()
{
	return SteelBowPlans::SaveKeySteelBowPlans;
}
