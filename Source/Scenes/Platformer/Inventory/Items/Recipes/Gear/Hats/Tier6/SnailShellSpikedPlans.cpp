#include "SnailShellSpikedPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SnailShellSpikedPlans::SaveKey = "snail-shell-spiked-plans";

SnailShellSpikedPlans* SnailShellSpikedPlans::create()
{
	SnailShellSpikedPlans* instance = new SnailShellSpikedPlans();

	instance->autorelease();

	return instance;
}

SnailShellSpikedPlans::SnailShellSpikedPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SnailShellSpikedPlans::~SnailShellSpikedPlans()
{
}

std::vector<Item*> SnailShellSpikedPlans::craft()
{
	return { SnailShellSpiked::create() };
}

std::vector<std::tuple<Item*, int>> SnailShellSpikedPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* SnailShellSpikedPlans::clone()
{
	return SnailShellSpikedPlans::create();
}

LocalizedString* SnailShellSpikedPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SnailShellSpiked::create();
}

const std::string& SnailShellSpikedPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SnailShellSpikedPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_SnailShellSpiked;
}

const std::string& SnailShellSpikedPlans::getIdentifier()
{
	return SnailShellSpikedPlans::SaveKey;
}
