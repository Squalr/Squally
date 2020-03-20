#include "Dreadmourn.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Dreadmourn::SaveKey = "dreadmourn";

Dreadmourn* Dreadmourn::create()
{
	Dreadmourn* instance = new Dreadmourn();

	instance->autorelease();

	return instance;
}

Dreadmourn::Dreadmourn() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 40, 48, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.15f
))
{
}

Dreadmourn::~Dreadmourn()
{
}

Item* Dreadmourn::clone()
{
	return Dreadmourn::create();
}

std::string Dreadmourn::getItemName()
{
	return Dreadmourn::SaveKey;
}

LocalizedString* Dreadmourn::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Dreadmourn::create();
}

std::string Dreadmourn::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_Dreadmourn;
}

std::string Dreadmourn::getSerializationKey()
{
	return Dreadmourn::SaveKey;
}
