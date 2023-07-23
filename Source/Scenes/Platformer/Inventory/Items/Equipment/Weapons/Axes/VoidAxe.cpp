#include "VoidAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/VoidAxePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidAxe::SaveKey = "void-axe";

VoidAxe* VoidAxe::create()
{
	VoidAxe* instance = new VoidAxe();

	instance->autorelease();

	return instance;
}

VoidAxe::VoidAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 11 }}), AXE_DAMAGE_MIN(9), AXE_DAMAGE_MAX(9), ItemStats(
	// Health
	4,
	// Mana
	5,
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

VoidAxe::~VoidAxe()
{
}

Item* VoidAxe::clone()
{
	return VoidAxe::create();
}

LocalizedString* VoidAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_VoidAxe::create();
}

const std::string& VoidAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_VoidAxe;
}

const std::string& VoidAxe::getIdentifier()
{
	return VoidAxe::SaveKey;
}

CSize VoidAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return CSize(112.0f, 96.0f);
}

Vec2 VoidAxe::getWeaponCollisionOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(-8.0f, 212.0f);
}

Vec2 VoidAxe::getDisplayOffset()
{
	return Vec2(0.0f, -8.0f);
}

Recipe* VoidAxe::getRecipe()
{
	return VoidAxePlans::create();
}
