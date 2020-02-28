#include "ArchersHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ArchersHat::SaveKeyArchersHat = "archers-hat";

ArchersHat* ArchersHat::create()
{
	ArchersHat* instance = new ArchersHat();

	instance->autorelease();

	return instance;
}

ArchersHat::ArchersHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

ArchersHat::~ArchersHat()
{
}

Item* ArchersHat::clone()
{
	return ArchersHat::create();
}

std::string ArchersHat::getItemName()
{
	return ArchersHat::SaveKeyArchersHat;
}

LocalizedString* ArchersHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string ArchersHat::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_ArchersHat;
}

std::string ArchersHat::getSerializationKey()
{
	return ArchersHat::SaveKeyArchersHat;
}

Vec2 ArchersHat::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
