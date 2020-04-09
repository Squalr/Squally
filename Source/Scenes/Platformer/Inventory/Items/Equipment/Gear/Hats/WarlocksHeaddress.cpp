#include "WarlocksHeaddress.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WarlocksHeaddress::SaveKey = "warlocks-headress";

WarlocksHeaddress* WarlocksHeaddress::create()
{
	WarlocksHeaddress* instance = new WarlocksHeaddress();

	instance->autorelease();

	return instance;
}

WarlocksHeaddress::WarlocksHeaddress() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

WarlocksHeaddress::~WarlocksHeaddress()
{
}

Item* WarlocksHeaddress::clone()
{
	return WarlocksHeaddress::create();
}

std::string WarlocksHeaddress::getItemName()
{
	return WarlocksHeaddress::SaveKey;
}

LocalizedString* WarlocksHeaddress::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WarlocksHeaddress::create();
}

std::string WarlocksHeaddress::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WarlocksHeaddress;
}

std::string WarlocksHeaddress::getSerializationKey()
{
	return WarlocksHeaddress::SaveKey;
}

Vec2 WarlocksHeaddress::getDisplayOffset()
{
	return Vec2(-10.0f, 40.0f);
}
