#include "CrystalSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalSword::SaveKey = "crystal-sword";

CrystalSword* CrystalSword::create()
{
	CrystalSword* instance = new CrystalSword();

	instance->autorelease();

	return instance;
}

CrystalSword::CrystalSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 56, 64, ItemStats(
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

CrystalSword::~CrystalSword()
{
}

Item* CrystalSword::clone()
{
	return CrystalSword::create();
}

std::string CrystalSword::getItemName()
{
	return CrystalSword::SaveKey;
}

LocalizedString* CrystalSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_CrystalSword::create();
}

std::string CrystalSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_CrystalSword;
}

std::string CrystalSword::getSerializationKey()
{
	return CrystalSword::SaveKey;
}
