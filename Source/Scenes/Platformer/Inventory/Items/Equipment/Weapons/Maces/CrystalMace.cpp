#include "CrystalMace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalMace::SaveKeyCrystalMace = "crystal-mace";

CrystalMace* CrystalMace::create()
{
	CrystalMace* instance = new CrystalMace();

	instance->autorelease();

	return instance;
}

CrystalMace::CrystalMace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 3, 6, ItemStats(
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

CrystalMace::~CrystalMace()
{
}

Item* CrystalMace::clone()
{
	return CrystalMace::create();
}

std::string CrystalMace::getItemName()
{
	return CrystalMace::SaveKeyCrystalMace;
}

LocalizedString* CrystalMace::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_CrystalMace::create();
}

std::string CrystalMace::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_CrystalMace;
}

std::string CrystalMace::getSerializationKey()
{
	return CrystalMace::SaveKeyCrystalMace;
}

Vec2 CrystalMace::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
