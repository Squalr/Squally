#include "WarlocksHeadress.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WarlocksHeadress::SaveKeyWarlocksHeadress = "warlocks-headress";

WarlocksHeadress* WarlocksHeadress::create()
{
	WarlocksHeadress* instance = new WarlocksHeadress();

	instance->autorelease();

	return instance;
}

WarlocksHeadress::WarlocksHeadress() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

WarlocksHeadress::~WarlocksHeadress()
{
}

Item* WarlocksHeadress::clone()
{
	return WarlocksHeadress::create();
}

std::string WarlocksHeadress::getItemName()
{
	return WarlocksHeadress::SaveKeyWarlocksHeadress;
}

LocalizedString* WarlocksHeadress::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string WarlocksHeadress::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_WarlocksHeadress;
}

std::string WarlocksHeadress::getSerializationKey()
{
	return WarlocksHeadress::SaveKeyWarlocksHeadress;
}

Vec2 WarlocksHeadress::getDisplayOffset()
{
	return Vec2(-10.0f, 40.0f);
}
