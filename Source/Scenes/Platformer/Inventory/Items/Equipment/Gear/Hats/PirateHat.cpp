#include "PirateHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PirateHat::SaveKeyPirateHat = "pirate-hat";

PirateHat* PirateHat::create()
{
	PirateHat* instance = new PirateHat();

	instance->autorelease();

	return instance;
}

PirateHat::PirateHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

PirateHat::~PirateHat()
{
}

Item* PirateHat::clone()
{
	return PirateHat::create();
}

std::string PirateHat::getItemName()
{
	return PirateHat::SaveKeyPirateHat;
}

LocalizedString* PirateHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_PirateHat::create();
}

std::string PirateHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_PirateHat;
}

std::string PirateHat::getSerializationKey()
{
	return PirateHat::SaveKeyPirateHat;
}

Vec2 PirateHat::getDisplayOffset()
{
	return Vec2(-12.0f, 2.0f);
}
