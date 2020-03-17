#include "Gladius.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Gladius::SaveKeyGladius = "gladius";

Gladius* Gladius::create()
{
	Gladius* instance = new Gladius();

	instance->autorelease();

	return instance;
}

Gladius::Gladius() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 10, 13, ItemStats(
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

Gladius::~Gladius()
{
}

Item* Gladius::clone()
{
	return Gladius::create();
}

std::string Gladius::getItemName()
{
	return Gladius::SaveKeyGladius;
}

LocalizedString* Gladius::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Gladius::create();
}

std::string Gladius::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_Gladius;
}

std::string Gladius::getSerializationKey()
{
	return Gladius::SaveKeyGladius;
}
