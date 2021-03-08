#include "TheGoldenEagle.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TheGoldenEagle::SaveKey = "the-golden-eagle";

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
	// Magic Attack
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

LocalizedString* TheGoldenEagle::getString()
{
	return Strings::Items_Equipment_Gear_Hats_TheGoldenEagle::create();
}

const std::string& TheGoldenEagle::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_TheGoldenEagle;
}

const std::string& TheGoldenEagle::getIdentifier()
{
	return TheGoldenEagle::SaveKey;
}

Vec2 TheGoldenEagle::getDisplayOffset()
{
	return Vec2(-42.0f, 6.0f);
}
