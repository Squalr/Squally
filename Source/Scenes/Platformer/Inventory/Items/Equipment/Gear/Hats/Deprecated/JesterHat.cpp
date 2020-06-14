#include "JesterHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string JesterHat::SaveKey = "jester-hat";

JesterHat* JesterHat::create()
{
	JesterHat* instance = new JesterHat();

	instance->autorelease();

	return instance;
}

JesterHat::JesterHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

JesterHat::~JesterHat()
{
}

Item* JesterHat::clone()
{
	return JesterHat::create();
}

std::string JesterHat::getItemName()
{
	return JesterHat::SaveKey;
}

LocalizedString* JesterHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_JesterHat::create();
}

std::string JesterHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_JesterHat;
}

std::string JesterHat::getSerializationKey()
{
	return JesterHat::SaveKey;
}

Vec2 JesterHat::getDisplayOffset()
{
	return Vec2(-34.0f, 14.0f);
}
