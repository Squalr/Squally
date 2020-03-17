#include "BlueSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BlueSwordPlans::SaveKeyBlueSwordPlans = "blue-sword-plans";

BlueSwordPlans* BlueSwordPlans::create()
{
	BlueSwordPlans* instance = new BlueSwordPlans();

	instance->autorelease();

	return instance;
}

BlueSwordPlans::BlueSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

BlueSwordPlans::~BlueSwordPlans()
{
}

Item* BlueSwordPlans::craft()
{
	return BlueSword::create();
}

std::vector<std::tuple<Item*, int>> BlueSwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* BlueSwordPlans::clone()
{
	return BlueSwordPlans::create();
}

std::string BlueSwordPlans::getItemName()
{
	return BlueSwordPlans::SaveKeyBlueSwordPlans;
}

LocalizedString* BlueSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_BlueSword::create();
}

std::string BlueSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string BlueSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_BlueSword;
}

std::string BlueSwordPlans::getSerializationKey()
{
	return BlueSwordPlans::SaveKeyBlueSwordPlans;
}
