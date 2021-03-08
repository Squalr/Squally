#include "SteelBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelBowPlans::SaveKey = "steel-bow-plans";

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

std::vector<Item*> SteelBowPlans::craft()
{
	return { SteelBow::create() };
}

std::vector<std::tuple<Item*, int>> SteelBowPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 8 },
		{ Iron::create(), 6 },
		{ Coal::create(), 4 },
	};
}

Item* SteelBowPlans::clone()
{
	return SteelBowPlans::create();
}

LocalizedString* SteelBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_SteelBow::create();
}

const std::string& SteelBowPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SteelBowPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_SteelBow;
}

const std::string& SteelBowPlans::getIdentifier()
{
	return SteelBowPlans::SaveKey;
}
