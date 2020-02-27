#include "CrystalWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalWand::SaveKeyCrystalWand = "crystal-wand";

CrystalWand* CrystalWand::create()
{
	CrystalWand* instance = new CrystalWand();

	instance->autorelease();

	return instance;
}

CrystalWand::CrystalWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 26, 32, ItemStats(
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

CrystalWand::~CrystalWand()
{
}

Item* CrystalWand::clone()
{
	return CrystalWand::create();
}

std::string CrystalWand::getItemName()
{
	return CrystalWand::SaveKeyCrystalWand;
}

LocalizedString* CrystalWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_CrystalWand::create();
}

std::string CrystalWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_CrystalWand;
}

std::string CrystalWand::getSerializationKey()
{
	return CrystalWand::SaveKeyCrystalWand;
}

Vec2 CrystalWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
