#include "BlueAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BlueAxe::SaveKeyBlueAxe = "blue-axe";

BlueAxe* BlueAxe::create()
{
	BlueAxe* instance = new BlueAxe();

	instance->autorelease();

	return instance;
}

BlueAxe::BlueAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
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

BlueAxe::~BlueAxe()
{
}

Item* BlueAxe::clone()
{
	return BlueAxe::create();
}

std::string BlueAxe::getItemName()
{
	return BlueAxe::SaveKeyBlueAxe;
}

LocalizedString* BlueAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_BlueAxe::create();
}

std::string BlueAxe::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_BlueAxe;
}

std::string BlueAxe::getSerializationKey()
{
	return BlueAxe::SaveKeyBlueAxe;
}

Size BlueAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 BlueAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
