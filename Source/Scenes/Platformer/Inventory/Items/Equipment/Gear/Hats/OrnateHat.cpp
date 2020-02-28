#include "OrnateHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OrnateHat::SaveKeyOrnateHat = "ornate-hat";

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
	return OrnateHat::SaveKeyOrnateHat;
}

LocalizedString* OrnateHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string OrnateHat::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_OrnateHat;
}

std::string OrnateHat::getSerializationKey()
{
	return OrnateHat::SaveKeyOrnateHat;
}

Vec2 OrnateHat::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
