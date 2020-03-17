#include "Scythe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Scythe::SaveKeyScythe = "scythe";

Scythe* Scythe::create()
{
	Scythe* instance = new Scythe();

	instance->autorelease();

	return instance;
}

Scythe::Scythe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
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

Scythe::~Scythe()
{
}

Item* Scythe::clone()
{
	return Scythe::create();
}

std::string Scythe::getItemName()
{
	return Scythe::SaveKeyScythe;
}

LocalizedString* Scythe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_Scythe::create();
}

std::string Scythe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_Scythe;
}

std::string Scythe::getSerializationKey()
{
	return Scythe::SaveKeyScythe;
}

Size Scythe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 Scythe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
