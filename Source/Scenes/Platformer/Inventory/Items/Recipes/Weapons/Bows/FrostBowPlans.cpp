#include "FrostBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FrostBowPlans::SaveKeyFrostBowPlans = "frost-bow-plans";

FrostBowPlans* FrostBowPlans::create()
{
	FrostBowPlans* instance = new FrostBowPlans();

	instance->autorelease();

	return instance;
}

FrostBowPlans::FrostBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

FrostBowPlans::~FrostBowPlans()
{
}

Item* FrostBowPlans::craft()
{
	return FrostBow::create();
}

std::vector<std::tuple<Item*, int>> FrostBowPlans::getReagentsInternal()
{
	return
	{
		{ Quartz::create(), 4 },
		{ Emerald::create(), 2 },
		{ Jade::create(), 2 },
		{ Iron::create(), 4 },
		{ Coal::create(), 4 },
	};
}

Item* FrostBowPlans::clone()
{
	return FrostBowPlans::create();
}

std::string FrostBowPlans::getItemName()
{
	return FrostBowPlans::SaveKeyFrostBowPlans;
}

LocalizedString* FrostBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_FrostBow::create();
}

std::string FrostBowPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string FrostBowPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_FrostBow;
}

std::string FrostBowPlans::getSerializationKey()
{
	return FrostBowPlans::SaveKeyFrostBowPlans;
}
