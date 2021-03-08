#include "CowboyHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CowboyHat::SaveKey = "cowboy-hat";

CowboyHat* CowboyHat::create()
{
	CowboyHat* instance = new CowboyHat();

	instance->autorelease();

	return instance;
}

CowboyHat::CowboyHat() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

CowboyHat::~CowboyHat()
{
}

Item* CowboyHat::clone()
{
	return CowboyHat::create();
}

const std::string& CowboyHat::getItemName()
{
	return CowboyHat::SaveKey;
}

LocalizedString* CowboyHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_CowboyHat::create();
}

const std::string& CowboyHat::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_CowboyHat;
}

const std::string& CowboyHat::getIdentifier()
{
	return CowboyHat::SaveKey;
}

Vec2 CowboyHat::getDisplayOffset()
{
	return Vec2(-10.0f, -24.0f);
}
