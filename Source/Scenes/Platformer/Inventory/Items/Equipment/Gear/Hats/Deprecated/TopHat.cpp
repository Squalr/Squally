#include "TopHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TopHat::SaveKey = "top-hat";

TopHat* TopHat::create()
{
	TopHat* instance = new TopHat();

	instance->autorelease();

	return instance;
}

TopHat::TopHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

TopHat::~TopHat()
{
}

Item* TopHat::clone()
{
	return TopHat::create();
}

const std::string& TopHat::getItemName()
{
	return TopHat::SaveKey;
}

LocalizedString* TopHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_TopHat::create();
}

const std::string& TopHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_TopHat;
}

const std::string& TopHat::getSerializationKey()
{
	return TopHat::SaveKey;
}

Vec2 TopHat::getDisplayOffset()
{
	return Vec2(-26.0f, 10.0f);
}
