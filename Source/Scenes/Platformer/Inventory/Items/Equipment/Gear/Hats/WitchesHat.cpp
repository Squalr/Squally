#include "WitchesHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WitchesHat::SaveKeyWitchesHat = "witches-hat";

WitchesHat* WitchesHat::create()
{
	WitchesHat* instance = new WitchesHat();

	instance->autorelease();

	return instance;
}

WitchesHat::WitchesHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

WitchesHat::~WitchesHat()
{
}

Item* WitchesHat::clone()
{
	return WitchesHat::create();
}

std::string WitchesHat::getItemName()
{
	return WitchesHat::SaveKeyWitchesHat;
}

LocalizedString* WitchesHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string WitchesHat::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_WitchesHat;
}

std::string WitchesHat::getSerializationKey()
{
	return WitchesHat::SaveKeyWitchesHat;
}

Vec2 WitchesHat::getDisplayOffset()
{
	return Vec2(-38.0f, 32.0f);
}
