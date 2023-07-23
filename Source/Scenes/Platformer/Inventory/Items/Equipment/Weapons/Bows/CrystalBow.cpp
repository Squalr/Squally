#include "CrystalBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/CrystalBowPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalBow::SaveKey = "crystal-bow";

CrystalBow* CrystalBow::create()
{
	CrystalBow* instance = new CrystalBow();

	instance->autorelease();

	return instance;
}

CrystalBow::CrystalBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), BOW_DAMAGE_MIN(8), BOW_DAMAGE_MAX(8), ItemStats(
	// Health
	3,
	// Mana
	8,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.25f
))
{
}

CrystalBow::~CrystalBow()
{
}

Item* CrystalBow::clone()
{
	return CrystalBow::create();
}

LocalizedString* CrystalBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_CrystalBow::create();
}

const std::string& CrystalBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_CrystalBow;
}

const std::string& CrystalBow::getIdentifier()
{
	return CrystalBow::SaveKey;
}

Vec2 CrystalBow::getDisplayOffset()
{
	return Vec2(-10.0f, -74.0f);
}

Recipe* CrystalBow::getRecipe()
{
	return CrystalBowPlans::create();
}
