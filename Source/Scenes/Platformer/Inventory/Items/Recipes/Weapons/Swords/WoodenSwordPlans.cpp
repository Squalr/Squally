#include "WoodenSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenSwordPlans::SaveKey = "wooden-sword-plans";

WoodenSwordPlans* WoodenSwordPlans::create()
{
	WoodenSwordPlans* instance = new WoodenSwordPlans();

	instance->autorelease();

	return instance;
}

WoodenSwordPlans::WoodenSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WoodenSwordPlans::~WoodenSwordPlans()
{
}

Item* WoodenSwordPlans::craft()
{
	return WoodenSword::create();
}

std::vector<std::tuple<Item*, int>> WoodenSwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
	};
}

Item* WoodenSwordPlans::clone()
{
	return WoodenSwordPlans::create();
}

std::string WoodenSwordPlans::getItemName()
{
	return WoodenSwordPlans::SaveKey;
}

LocalizedString* WoodenSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_WoodenSword::create();
}

std::string WoodenSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WoodenSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_WoodenSword;
}

std::string WoodenSwordPlans::getSerializationKey()
{
	return WoodenSwordPlans::SaveKey;
}
