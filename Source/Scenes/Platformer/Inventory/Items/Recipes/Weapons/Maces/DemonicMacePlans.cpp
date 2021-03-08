#include "DemonicMacePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonicMacePlans::SaveKey = "demonic-mace-plans";

DemonicMacePlans* DemonicMacePlans::create()
{
	DemonicMacePlans* instance = new DemonicMacePlans();

	instance->autorelease();

	return instance;
}

DemonicMacePlans::DemonicMacePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

DemonicMacePlans::~DemonicMacePlans()
{
}

std::vector<Item*> DemonicMacePlans::craft()
{
	return { DemonicMace::create() };
}

std::vector<std::tuple<Item*, int>> DemonicMacePlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 8 },
		{ Coal::create(), 8 },
		{ Copper::create(), 8 },
		{ Sulfur::create(), 6 },
	};
}

Item* DemonicMacePlans::clone()
{
	return DemonicMacePlans::create();
}

const std::string& DemonicMacePlans::getItemName()
{
	return DemonicMacePlans::SaveKey;
}

LocalizedString* DemonicMacePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_DemonicMace::create();
}

const std::string& DemonicMacePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DemonicMacePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_DemonicMace;
}

const std::string& DemonicMacePlans::getIdentifier()
{
	return DemonicMacePlans::SaveKey;
}
