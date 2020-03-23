#include "DemonicAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

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

DemonicAxe::DemonicAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
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

std::string DemonicAxe::getItemName()
{
	return DemonicAxe::SaveKey;
}

LocalizedString* DemonicAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_DemonicAxe::create();
}

std::string DemonicAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_DemonicAxe;
}

std::string DemonicAxe::getSerializationKey()
{
	return DemonicAxe::SaveKey;
}

Size DemonicAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 DemonicAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}

Vec2 DemonicAxe::getDisplayOffset()
{
	return Vec2(28.0f, -4.0f);
}
