#include "OrnateHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OrnateHat::SaveKey = "ornate-hat";

OrnateHat* OrnateHat::create()
{
	OrnateHat* instance = new OrnateHat();

	instance->autorelease();

	return instance;
}

OrnateHat::OrnateHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

OrnateHat::~OrnateHat()
{
}

Item* OrnateHat::clone()
{
	return OrnateHat::create();
}

std::string OrnateHat::getItemName()
{
	return OrnateHat::SaveKey;
}

LocalizedString* OrnateHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_OrnateHat::create();
}

std::string OrnateHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_OrnateHat;
}

std::string OrnateHat::getSerializationKey()
{
	return OrnateHat::SaveKey;
}

Vec2 OrnateHat::getDisplayOffset()
{
	return Vec2(-22.0f, -6.0f);
}
