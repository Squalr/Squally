#include "WitchesHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WitchesHat::SaveKey = "witches-hat";

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
	return WitchesHat::SaveKey;
}

LocalizedString* WitchesHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WitchesHat::create();
}

std::string WitchesHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WitchesHat;
}

std::string WitchesHat::getSerializationKey()
{
	return WitchesHat::SaveKey;
}

Vec2 WitchesHat::getDisplayOffset()
{
	return Vec2(-38.0f, 32.0f);
}
