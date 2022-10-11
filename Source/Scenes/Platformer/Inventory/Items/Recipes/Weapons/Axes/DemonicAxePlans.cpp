#include "DemonicAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonicAxePlans::SaveKey = "demonic-axe-plans";

DemonicAxePlans* DemonicAxePlans::create()
{
	DemonicAxePlans* instance = new DemonicAxePlans();

	instance->autorelease();

	return instance;
}

DemonicAxePlans::DemonicAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

DemonicAxePlans::~DemonicAxePlans()
{
}

std::vector<Item*> DemonicAxePlans::craft()
{
	return { DemonicAxe::create() };
}

std::vector<std::tuple<Item*, int>> DemonicAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* DemonicAxePlans::clone()
{
	return DemonicAxePlans::create();
}

LocalizedString* DemonicAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_DemonicAxe::create();
}

const std::string& DemonicAxePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DemonicAxePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_DemonicAxe;
}

const std::string& DemonicAxePlans::getIdentifier()
{
	return DemonicAxePlans::SaveKey;
}
