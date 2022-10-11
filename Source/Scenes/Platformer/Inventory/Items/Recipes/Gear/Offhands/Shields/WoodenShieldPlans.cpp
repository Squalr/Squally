#include "WoodenShieldPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenShieldPlans::SaveKey = "wooden-shield-plans";

WoodenShieldPlans* WoodenShieldPlans::create()
{
	WoodenShieldPlans* instance = new WoodenShieldPlans();

	instance->autorelease();

	return instance;
}

WoodenShieldPlans::WoodenShieldPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WoodenShieldPlans::~WoodenShieldPlans()
{
}

std::vector<Item*> WoodenShieldPlans::craft()
{
	return { WoodenShield::create() };
}

std::vector<std::tuple<Item*, int>> WoodenShieldPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WoodenShieldPlans::clone()
{
	return WoodenShieldPlans::create();
}

LocalizedString* WoodenShieldPlans::getString()
{
	return Strings::Items_Equipment_Offhands_Shields_WoodenShield::create();
}

const std::string& WoodenShieldPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WoodenShieldPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Offhands_Shields_WoodenShield;
}

const std::string& WoodenShieldPlans::getIdentifier()
{
	return WoodenShieldPlans::SaveKey;
}
