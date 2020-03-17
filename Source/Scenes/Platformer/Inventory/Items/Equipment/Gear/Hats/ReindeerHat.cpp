#include "ReindeerHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ReindeerHat::SaveKeyReindeerHat = "reindeer-hat";

ReindeerHat* ReindeerHat::create()
{
	ReindeerHat* instance = new ReindeerHat();

	instance->autorelease();

	return instance;
}

ReindeerHat::ReindeerHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

ReindeerHat::~ReindeerHat()
{
}

Item* ReindeerHat::clone()
{
	return ReindeerHat::create();
}

std::string ReindeerHat::getItemName()
{
	return ReindeerHat::SaveKeyReindeerHat;
}

LocalizedString* ReindeerHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_ReindeerHat::create();
}

std::string ReindeerHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_ReindeerHat;
}

std::string ReindeerHat::getSerializationKey()
{
	return ReindeerHat::SaveKeyReindeerHat;
}

Vec2 ReindeerHat::getDisplayOffset()
{
	return Vec2(-12.0f, 6.0f);
}
