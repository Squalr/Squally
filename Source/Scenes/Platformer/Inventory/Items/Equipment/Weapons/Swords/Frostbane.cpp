#include "Frostbane.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Frostbane::SaveKeyFrostbane = "frost-bane";

Frostbane* Frostbane::create()
{
	Frostbane* instance = new Frostbane();

	instance->autorelease();

	return instance;
}

Frostbane::Frostbane() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 32, ItemStats(
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

Frostbane::~Frostbane()
{
}

Item* Frostbane::clone()
{
	return Frostbane::create();
}

std::string Frostbane::getItemName()
{
	return Frostbane::SaveKeyFrostbane;
}

LocalizedString* Frostbane::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Frostbane::create();
}

std::string Frostbane::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_Frostbane;
}

std::string Frostbane::getSerializationKey()
{
	return Frostbane::SaveKeyFrostbane;
}
