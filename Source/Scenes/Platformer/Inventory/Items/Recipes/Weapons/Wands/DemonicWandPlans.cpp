#include "DemonicWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonicWandPlans::SaveKey = "demonic-wand-plans";

DemonicWandPlans* DemonicWandPlans::create()
{
	DemonicWandPlans* instance = new DemonicWandPlans();

	instance->autorelease();

	return instance;
}

DemonicWandPlans::DemonicWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

DemonicWandPlans::~DemonicWandPlans()
{
}

std::vector<Item*> DemonicWandPlans::craft()
{
	return { DemonicWand::create() };
}

std::vector<std::tuple<Item*, int>> DemonicWandPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
		{ Gold::create(), 4 },
		{ Emerald::create(), 2 },
		{ Sapphire::create(), 3 },
	};
}

Item* DemonicWandPlans::clone()
{
	return DemonicWandPlans::create();
}

LocalizedString* DemonicWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_DemonicWand::create();
}

const std::string& DemonicWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DemonicWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_DemonicWand;
}

const std::string& DemonicWandPlans::getIdentifier()
{
	return DemonicWandPlans::SaveKey;
}
