#include "SapphireWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SapphireWandPlans::SaveKey = "serpent-wand-plans";

SapphireWandPlans* SapphireWandPlans::create()
{
	SapphireWandPlans* instance = new SapphireWandPlans();

	instance->autorelease();

	return instance;
}

SapphireWandPlans::SapphireWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SapphireWandPlans::~SapphireWandPlans()
{
}

Item* SapphireWandPlans::craft()
{
	return SerpentWand::create();
}

std::vector<std::tuple<Item*, int>> SapphireWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
		{ Gold::create(), 1 },
		{ Emerald::create(), 1 },
		{ Ruby::create(), 1 },
	};
}

Item* SapphireWandPlans::clone()
{
	return SapphireWandPlans::create();
}

std::string SapphireWandPlans::getItemName()
{
	return SapphireWandPlans::SaveKey;
}

LocalizedString* SapphireWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_SapphireWand::create();
}

std::string SapphireWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SapphireWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_SapphireWand;
}

std::string SapphireWandPlans::getSerializationKey()
{
	return SapphireWandPlans::SaveKey;
}
