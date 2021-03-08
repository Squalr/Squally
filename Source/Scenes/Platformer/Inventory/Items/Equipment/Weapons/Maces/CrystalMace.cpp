#include "CrystalMace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/CrystalMacePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalMace::SaveKey = "crystal-mace";

CrystalMace* CrystalMace::create()
{
	CrystalMace* instance = new CrystalMace();

	instance->autorelease();

	return instance;
}

CrystalMace::CrystalMace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 56, 64, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
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

const std::string& CrystalMace::getItemName()
{
	return CrystalMace::SaveKey;
}

LocalizedString* CrystalMace::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_CrystalMace::create();
}

const std::string& CrystalMace::getIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_CrystalMace;
}

const std::string& CrystalMace::getSerializationKey()
{
	return CrystalMace::SaveKey;
}

Vec2 CrystalMace::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* CrystalMace::getRecipe()
{
	return CrystalMacePlans::create();
}
