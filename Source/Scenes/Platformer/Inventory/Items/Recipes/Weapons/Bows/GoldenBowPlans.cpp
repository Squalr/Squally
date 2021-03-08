#include "GoldenBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenBowPlans::SaveKey = "golden-bow-plans";

GoldenBowPlans* GoldenBowPlans::create()
{
	GoldenBowPlans* instance = new GoldenBowPlans();

	instance->autorelease();

	return instance;
}

GoldenBowPlans::GoldenBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GoldenBowPlans::~GoldenBowPlans()
{
}

std::vector<Item*> GoldenBowPlans::craft()
{
	return { GoldenBow::create() };
}

std::vector<std::tuple<Item*, int>> GoldenBowPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
		{ Iron::create(), 4 },
		{ Coal::create(), 4 },
		{ Gold::create(), 4 },
	};
}

Item* GoldenBowPlans::clone()
{
	return GoldenBowPlans::create();
}

const std::string& GoldenBowPlans::getItemName()
{
	return GoldenBowPlans::SaveKey;
}

LocalizedString* GoldenBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_GoldenBow::create();
}

const std::string& GoldenBowPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GoldenBowPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_GoldenBow;
}

const std::string& GoldenBowPlans::getIdentifier()
{
	return GoldenBowPlans::SaveKey;
}
