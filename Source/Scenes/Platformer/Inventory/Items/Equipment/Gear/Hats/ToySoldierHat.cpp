#include "ToySoldierHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ToySoldierHat::SaveKeyToySoldierHat = "toy-soldier-hat";

ToySoldierHat* ToySoldierHat::create()
{
	ToySoldierHat* instance = new ToySoldierHat();

	instance->autorelease();

	return instance;
}

ToySoldierHat::ToySoldierHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

ToySoldierHat::~ToySoldierHat()
{
}

Item* ToySoldierHat::clone()
{
	return ToySoldierHat::create();
}

std::string ToySoldierHat::getItemName()
{
	return ToySoldierHat::SaveKeyToySoldierHat;
}

LocalizedString* ToySoldierHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_ToySoldierHat::create();
}

std::string ToySoldierHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_ToySoldierHat;
}

std::string ToySoldierHat::getSerializationKey()
{
	return ToySoldierHat::SaveKeyToySoldierHat;
}

Vec2 ToySoldierHat::getDisplayOffset()
{
	return Vec2(16.0f, 8.0f);
}
