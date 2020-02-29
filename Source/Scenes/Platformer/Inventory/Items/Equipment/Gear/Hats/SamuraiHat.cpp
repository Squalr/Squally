#include "SamuraiHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SamuraiHat::SaveKeySamuraiHat = "samurai-hat";

SamuraiHat* SamuraiHat::create()
{
	SamuraiHat* instance = new SamuraiHat();

	instance->autorelease();

	return instance;
}

SamuraiHat::SamuraiHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

SamuraiHat::~SamuraiHat()
{
}

Item* SamuraiHat::clone()
{
	return SamuraiHat::create();
}

std::string SamuraiHat::getItemName()
{
	return SamuraiHat::SaveKeySamuraiHat;
}

LocalizedString* SamuraiHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string SamuraiHat::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_SamuraiHat;
}

std::string SamuraiHat::getSerializationKey()
{
	return SamuraiHat::SaveKeySamuraiHat;
}

Vec2 SamuraiHat::getDisplayOffset()
{
	return Vec2(-18.0f, -10.0f);
}
