#include "GardenersHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GardenersHat::SaveKey = "gardeners-hat";

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
	// Magic Attack
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

LocalizedString* GardenersHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_GardenersHat::create();
}

const std::string& GardenersHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_GardenersHat;
}

const std::string& GardenersHat::getIdentifier()
{
	return GardenersHat::SaveKey;
}

Vec2 GardenersHat::getDisplayOffset()
{
	return Vec2(-12.0f, -2.0f);
}
