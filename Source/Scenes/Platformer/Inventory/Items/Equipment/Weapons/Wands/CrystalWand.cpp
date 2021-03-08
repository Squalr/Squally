#include "CrystalWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/CrystalWandPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalWand::SaveKey = "crystal-wand";

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
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.15f
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

const std::string& CrystalWand::getItemName()
{
	return CrystalWand::SaveKey;
}

LocalizedString* CrystalWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_CrystalWand::create();
}

const std::string& CrystalWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_CrystalWand;
}

const std::string& CrystalWand::getSerializationKey()
{
	return CrystalWand::SaveKey;
}

Vec2 CrystalWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}

Recipe* CrystalWand::getRecipe()
{
	return CrystalWandPlans::create();
}
