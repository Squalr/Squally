#include "BlueSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BlueSword::SaveKeyBlueSword = "blue-sword";

BlueSword* BlueSword::create()
{
	BlueSword* instance = new BlueSword();

	instance->autorelease();

	return instance;
}

BlueSword::BlueSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 32, ItemStats(
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

BlueSword::~BlueSword()
{
}

Item* BlueSword::clone()
{
	return BlueSword::create();
}

std::string BlueSword::getItemName()
{
	return BlueSword::SaveKeyBlueSword;
}

LocalizedString* BlueSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_BlueSword::create();
}

std::string BlueSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_BlueSword;
}

std::string BlueSword::getSerializationKey()
{
	return BlueSword::SaveKeyBlueSword;
}
