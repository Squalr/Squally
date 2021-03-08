#include "WitchesWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WitchesWandPlans::SaveKey = "witches-wand-plans";

WitchesWandPlans* WitchesWandPlans::create()
{
	WitchesWandPlans* instance = new WitchesWandPlans();

	instance->autorelease();

	return instance;
}

WitchesWandPlans::WitchesWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WitchesWandPlans::~WitchesWandPlans()
{
}

std::vector<Item*> WitchesWandPlans::craft()
{
	return { TaserRod::create() };
}

std::vector<std::tuple<Item*, int>> WitchesWandPlans::getReagentsInternal()
{
	return
	{
		{ Sapphire::create(), 4 },
		{ Sulfur::create(), 1 },
	};
}

Item* WitchesWandPlans::clone()
{
	return WitchesWandPlans::create();
}

const std::string& WitchesWandPlans::getItemName()
{
	return WitchesWandPlans::SaveKey;
}

LocalizedString* WitchesWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_WitchesWand::create();
}

const std::string& WitchesWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WitchesWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Special_WitchesWand;
}

const std::string& WitchesWandPlans::getIdentifier()
{
	return WitchesWandPlans::SaveKey;
}
