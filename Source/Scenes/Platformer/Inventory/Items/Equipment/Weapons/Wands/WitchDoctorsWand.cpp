#include "WitchDoctorsWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WitchDoctorsWand::SaveKeyWitchDoctorsWand = "witch-doctors-wand";

WitchDoctorsWand* WitchDoctorsWand::create()
{
	WitchDoctorsWand* instance = new WitchDoctorsWand();

	instance->autorelease();

	return instance;
}

WitchDoctorsWand::WitchDoctorsWand() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6, ItemStats(
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

WitchDoctorsWand::~WitchDoctorsWand()
{
}

Item* WitchDoctorsWand::clone()
{
	return WitchDoctorsWand::create();
}

std::string WitchDoctorsWand::getItemName()
{
	return WitchDoctorsWand::SaveKeyWitchDoctorsWand;
}

LocalizedString* WitchDoctorsWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_WitchDoctorsWand::create();
}

std::string WitchDoctorsWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_WitchDoctorsWand;
}

std::string WitchDoctorsWand::getSerializationKey()
{
	return WitchDoctorsWand::SaveKeyWitchDoctorsWand;
}

Vec2 WitchDoctorsWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
