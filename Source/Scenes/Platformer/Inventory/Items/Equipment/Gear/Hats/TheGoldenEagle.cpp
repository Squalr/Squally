#include "TheGoldenEagle.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TheGoldenEagle::SaveKeyTheGoldenEagle = "the-golden-eagle";

TheGoldenEagle* TheGoldenEagle::create()
{
	TheGoldenEagle* instance = new TheGoldenEagle();

	instance->autorelease();

	return instance;
}

TheGoldenEagle::TheGoldenEagle() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

TheGoldenEagle::~TheGoldenEagle()
{
}

Item* TheGoldenEagle::clone()
{
	return TheGoldenEagle::create();
}

std::string TheGoldenEagle::getItemName()
{
	return TheGoldenEagle::SaveKeyTheGoldenEagle;
}

LocalizedString* TheGoldenEagle::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string TheGoldenEagle::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_TheGoldenEagle;
}

std::string TheGoldenEagle::getSerializationKey()
{
	return TheGoldenEagle::SaveKeyTheGoldenEagle;
}

Vec2 TheGoldenEagle::getDisplayOffset()
{
	return Vec2(-42.0f, 6.0f);
}
