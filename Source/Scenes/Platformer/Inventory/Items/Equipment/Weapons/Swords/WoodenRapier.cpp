#include "WoodenRapier.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenRapier::SaveKeyWoodenRapier = "wooden-rapier";

WoodenRapier* WoodenRapier::create()
{
	WoodenRapier* instance = new WoodenRapier();

	instance->autorelease();

	return instance;
}

WoodenRapier::WoodenRapier() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 9 }}), 8, 11, ItemStats(
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

WoodenRapier::~WoodenRapier()
{
}

Item* WoodenRapier::clone()
{
	return WoodenRapier::create();
}

std::string WoodenRapier::getItemName()
{
	return WoodenRapier::SaveKeyWoodenRapier;
}

LocalizedString* WoodenRapier::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_WoodenRapier::create();
}

std::string WoodenRapier::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_WoodenRapier;
}

std::string WoodenRapier::getSerializationKey()
{
	return WoodenRapier::SaveKeyWoodenRapier;
}
