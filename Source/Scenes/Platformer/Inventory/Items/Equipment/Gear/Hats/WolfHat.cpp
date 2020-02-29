#include "WolfHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WolfHat::SaveKeyWolfHat = "wolf-hat";

WolfHat* WolfHat::create()
{
	WolfHat* instance = new WolfHat();

	instance->autorelease();

	return instance;
}

WolfHat::WolfHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

WolfHat::~WolfHat()
{
}

Item* WolfHat::clone()
{
	return WolfHat::create();
}

std::string WolfHat::getItemName()
{
	return WolfHat::SaveKeyWolfHat;
}

LocalizedString* WolfHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WolfHat::create();
}

std::string WolfHat::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_WolfHat;
}

std::string WolfHat::getSerializationKey()
{
	return WolfHat::SaveKeyWolfHat;
}

Vec2 WolfHat::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
