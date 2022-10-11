#include "DemonShellPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonShellPlans::SaveKey = "demon-shell-plans";

DemonShellPlans* DemonShellPlans::create()
{
	DemonShellPlans* instance = new DemonShellPlans();

	instance->autorelease();

	return instance;
}

DemonShellPlans::DemonShellPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

DemonShellPlans::~DemonShellPlans()
{
}

std::vector<Item*> DemonShellPlans::craft()
{
	return { DemonShell::create() };
}

std::vector<std::tuple<Item*, int>> DemonShellPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* DemonShellPlans::clone()
{
	return DemonShellPlans::create();
}

LocalizedString* DemonShellPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_DemonShell::create();
}

const std::string& DemonShellPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DemonShellPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_DemonShell;
}

const std::string& DemonShellPlans::getIdentifier()
{
	return DemonShellPlans::SaveKey;
}
