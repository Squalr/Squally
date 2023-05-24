#include "CrystalAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/CrystalAxePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalAxe::SaveKey = "crystal-axe";

CrystalAxe* CrystalAxe::create()
{
	CrystalAxe* instance = new CrystalAxe();

	instance->autorelease();

	return instance;
}

CrystalAxe::CrystalAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), AXE_DAMAGE_MIN(8), AXE_DAMAGE_MIN(8), ItemStats(
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
	0.10f
))
{
}

CrystalAxe::~CrystalAxe()
{
}

Item* CrystalAxe::clone()
{
	return CrystalAxe::create();
}

LocalizedString* CrystalAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_CrystalAxe::create();
}

const std::string& CrystalAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_CrystalAxe;
}

const std::string& CrystalAxe::getIdentifier()
{
	return CrystalAxe::SaveKey;
}

CSize CrystalAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return CSize(112.0f, 96.0f);
}

Vec2 CrystalAxe::getWeaponCollisionOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(-12.0f, 212.0f);
}

Vec2 CrystalAxe::getDisplayOffset()
{
	return Vec2(0.0f, -8.0f);
}

Recipe* CrystalAxe::getRecipe()
{
	return CrystalAxePlans::create();
}
