#include "AshenBlade.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AshenBlade::SaveKeyAshenBlade = "ashen-blade";

AshenBlade* AshenBlade::create()
{
	AshenBlade* instance = new AshenBlade();

	instance->autorelease();

	return instance;
}

AshenBlade::AshenBlade() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 48, 56, ItemStats(
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

AshenBlade::~AshenBlade()
{
}

Item* AshenBlade::clone()
{
	return AshenBlade::create();
}

std::string AshenBlade::getItemName()
{
	return AshenBlade::SaveKeyAshenBlade;
}

LocalizedString* AshenBlade::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_AshenBlade::create();
}

std::string AshenBlade::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_AshenBlade;
}

std::string AshenBlade::getSerializationKey()
{
	return AshenBlade::SaveKeyAshenBlade;
}
