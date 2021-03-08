#include "GrandpasLuckyHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GrandpasLuckyHat::SaveKey = "grandpas-lucky-hat";

GrandpasLuckyHat* GrandpasLuckyHat::create()
{
	GrandpasLuckyHat* instance = new GrandpasLuckyHat();

	instance->autorelease();

	return instance;
}

GrandpasLuckyHat::GrandpasLuckyHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 11 }}), ItemStats(
	// Health
	1,
	// Mana
	1,
	// Attack
	1,
	// Magic Attack
	0,
	// Armor
	1,
	// Speed
	0.05f
))
{
}

GrandpasLuckyHat::~GrandpasLuckyHat()
{
}

Item* GrandpasLuckyHat::clone()
{
	return GrandpasLuckyHat::create();
}

LocalizedString* GrandpasLuckyHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_GrandpasLuckyHat::create();
}

const std::string& GrandpasLuckyHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_GrandpasLuckyHat;
}

const std::string& GrandpasLuckyHat::getIdentifier()
{
	return GrandpasLuckyHat::SaveKey;
}

Vec2 GrandpasLuckyHat::getDisplayOffset()
{
	return Vec2(6.0f, -26.0f);
}
