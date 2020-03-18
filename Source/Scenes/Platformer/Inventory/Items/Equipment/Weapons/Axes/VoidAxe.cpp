#include "VoidAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidAxe::SaveKeyVoidAxe = "void-axe";

VoidAxe* VoidAxe::create()
{
	VoidAxe* instance = new VoidAxe();

	instance->autorelease();

	return instance;
}

VoidAxe::VoidAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 11 }}), 4, 7, ItemStats(
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

VoidAxe::~VoidAxe()
{
}

Item* VoidAxe::clone()
{
	return VoidAxe::create();
}

std::string VoidAxe::getItemName()
{
	return VoidAxe::SaveKeyVoidAxe;
}

LocalizedString* VoidAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_VoidAxe::create();
}

std::string VoidAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_VoidAxe;
}

std::string VoidAxe::getSerializationKey()
{
	return VoidAxe::SaveKeyVoidAxe;
}

Size VoidAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 VoidAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
