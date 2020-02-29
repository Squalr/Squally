#include "WolfHatWhite.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WolfHatWhite::SaveKeyWolfHatWhite = "wolf-hat-white";

WolfHatWhite* WolfHatWhite::create()
{
	WolfHatWhite* instance = new WolfHatWhite();

	instance->autorelease();

	return instance;
}

WolfHatWhite::WolfHatWhite() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

WolfHatWhite::~WolfHatWhite()
{
}

Item* WolfHatWhite::clone()
{
	return WolfHatWhite::create();
}

std::string WolfHatWhite::getItemName()
{
	return WolfHatWhite::SaveKeyWolfHatWhite;
}

LocalizedString* WolfHatWhite::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WolfHatWhite::create();
}

std::string WolfHatWhite::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_WolfHatWhite;
}

std::string WolfHatWhite::getSerializationKey()
{
	return WolfHatWhite::SaveKeyWolfHatWhite;
}

Vec2 WolfHatWhite::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
