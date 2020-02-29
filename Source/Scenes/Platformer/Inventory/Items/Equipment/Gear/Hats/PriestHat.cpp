#include "PriestHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PriestHat::SaveKeyPriestHat = "priest-hat";

PriestHat* PriestHat::create()
{
	PriestHat* instance = new PriestHat();

	instance->autorelease();

	return instance;
}

PriestHat::PriestHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

PriestHat::~PriestHat()
{
}

Item* PriestHat::clone()
{
	return PriestHat::create();
}

std::string PriestHat::getItemName()
{
	return PriestHat::SaveKeyPriestHat;
}

LocalizedString* PriestHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_PriestHat::create();
}

std::string PriestHat::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_PriestHat;
}

std::string PriestHat::getSerializationKey()
{
	return PriestHat::SaveKeyPriestHat;
}

Vec2 PriestHat::getDisplayOffset()
{
	return Vec2(-10.0f, 24.0f);
}
