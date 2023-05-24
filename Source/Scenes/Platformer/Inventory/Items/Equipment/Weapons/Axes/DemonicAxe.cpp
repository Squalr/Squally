#include "DemonicAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/DemonicAxePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DemonicAxe::SaveKey = "demonic-axe";

DemonicAxe* DemonicAxe::create()
{
	DemonicAxe* instance = new DemonicAxe();

	instance->autorelease();

	return instance;
}

DemonicAxe::DemonicAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), AXE_DAMAGE_MIN(7), AXE_DAMAGE_MIN(7), ItemStats(
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

DemonicAxe::~DemonicAxe()
{
}

Item* DemonicAxe::clone()
{
	return DemonicAxe::create();
}

LocalizedString* DemonicAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_DemonicAxe::create();
}

const std::string& DemonicAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_DemonicAxe;
}

const std::string& DemonicAxe::getIdentifier()
{
	return DemonicAxe::SaveKey;
}

CSize DemonicAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return CSize(112.0f, 96.0f);
}

Vec2 DemonicAxe::getWeaponCollisionOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(-12.0f, 212.0f);
}

Vec2 DemonicAxe::getDisplayOffset()
{
	return Vec2(0.0f, -8.0f);
}

Recipe* DemonicAxe::getRecipe()
{
	return DemonicAxePlans::create();
}
