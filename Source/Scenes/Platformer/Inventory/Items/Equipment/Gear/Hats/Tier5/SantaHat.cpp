#include "SantaHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SantaHat::SaveKey = "santa-hat";

SantaHat* SantaHat::create()
{
	SantaHat* instance = new SantaHat();

	instance->autorelease();

	return instance;
}

SantaHat::SantaHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

SantaHat::~SantaHat()
{
}

Item* SantaHat::clone()
{
	return SantaHat::create();
}

const std::string& SantaHat::getItemName()
{
	return SantaHat::SaveKey;
}

LocalizedString* SantaHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

const std::string& SantaHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_SantaHat;
}

const std::string& SantaHat::getSerializationKey()
{
	return SantaHat::SaveKey;
}

Vec2 SantaHat::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
