#include "Scythe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Scythe::SaveKeyScythe = "scythe";

Scythe* Scythe::create()
{
	Scythe* instance = new Scythe();

	instance->autorelease();

	return instance;
}

Scythe::Scythe() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 4, 7)
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
	return ObjectResources::Items_Equipment_Weapons_Axes_Scythe;
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
