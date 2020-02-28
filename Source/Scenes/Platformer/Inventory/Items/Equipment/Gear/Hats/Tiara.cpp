#include "Tiara.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tiara::SaveKeyTiara = "tiara";

Tiara* Tiara::create()
{
	Tiara* instance = new Tiara();

	instance->autorelease();

	return instance;
}

Tiara::Tiara() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

Tiara::~Tiara()
{
}

Item* Tiara::clone()
{
	return Tiara::create();
}

std::string Tiara::getItemName()
{
	return Tiara::SaveKeyTiara;
}

LocalizedString* Tiara::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string Tiara::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_Tiara;
}

std::string Tiara::getSerializationKey()
{
	return Tiara::SaveKeyTiara;
}

Vec2 Tiara::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
