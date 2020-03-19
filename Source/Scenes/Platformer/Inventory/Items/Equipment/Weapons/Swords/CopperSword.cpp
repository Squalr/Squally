#include "CopperSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperSword::SaveKey = "copper-sword";

CopperSword* CopperSword::create()
{
	CopperSword* instance = new CopperSword();

	instance->autorelease();

	return instance;
}

CopperSword::CopperSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), 6, 8, ItemStats(
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

CopperSword::~CopperSword()
{
}

Item* CopperSword::clone()
{
	return CopperSword::create();
}

std::string CopperSword::getItemName()
{
	return CopperSword::SaveKey;
}

LocalizedString* CopperSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_CopperSword::create();
}

std::string CopperSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_CopperSword;
}

std::string CopperSword::getSerializationKey()
{
	return CopperSword::SaveKey;
}
