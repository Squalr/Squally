#include "GardenersHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GardenersHat::SaveKeyGardenersHat = "gardeners-hat";

GardenersHat* GardenersHat::create()
{
	GardenersHat* instance = new GardenersHat();

	instance->autorelease();

	return instance;
}

GardenersHat::GardenersHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

GardenersHat::~GardenersHat()
{
}

Item* GardenersHat::clone()
{
	return GardenersHat::create();
}

std::string GardenersHat::getItemName()
{
	return GardenersHat::SaveKeyGardenersHat;
}

LocalizedString* GardenersHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string GardenersHat::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_GardenersHat;
}

std::string GardenersHat::getSerializationKey()
{
	return GardenersHat::SaveKeyGardenersHat;
}

Vec2 GardenersHat::getDisplayOffset()
{
	return Vec2(-12.0f, -2.0f);
}
