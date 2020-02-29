#include "WarlocksHeaddress.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WarlocksHeaddress::SaveKeyWarlocksHeaddress = "warlocks-headress";

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
	return WarlocksHeaddress::SaveKeyWarlocksHeaddress;
}

LocalizedString* WarlocksHeaddress::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WarlocksHeaddress::create();
}

std::string WarlocksHeaddress::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_WarlocksHeaddress;
}

std::string WarlocksHeaddress::getSerializationKey()
{
	return WarlocksHeaddress::SaveKeyWarlocksHeaddress;
}

Vec2 WarlocksHeaddress::getDisplayOffset()
{
	return Vec2(-10.0f, 40.0f);
}
