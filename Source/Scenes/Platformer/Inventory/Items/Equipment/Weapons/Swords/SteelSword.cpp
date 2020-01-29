#include "SteelSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelSword::SaveKeySteelSword = "steel-sword";

SteelSword* SteelSword::create()
{
	SteelSword* instance = new SteelSword();

	instance->autorelease();

	return instance;
}

SteelSword::SteelSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 3, 6, ItemStats(
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

SteelSword::~SteelSword()
{
}

Item* SteelSword::clone()
{
	return SteelSword::create();
}

std::string SteelSword::getItemName()
{
	return SteelSword::SaveKeySteelSword;
}

LocalizedString* SteelSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_SteelSword::create();
}

std::string SteelSword::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_SteelSword;
}

std::string SteelSword::getSerializationKey()
{
	return SteelSword::SaveKeySteelSword;
}
