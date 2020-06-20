#include "CopperAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperAxe::SaveKey = "copper-axe";

CopperAxe* CopperAxe::create()
{
	CopperAxe* instance = new CopperAxe();

	instance->autorelease();

	return instance;
}

CopperAxe::CopperAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 6, 9, ItemStats(
	// Health
	2,
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

CopperAxe::~CopperAxe()
{
}

Item* CopperAxe::clone()
{
	return CopperAxe::create();
}

std::string CopperAxe::getItemName()
{
	return CopperAxe::SaveKey;
}

LocalizedString* CopperAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_CopperAxe::create();
}

std::string CopperAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_CopperAxe;
}

std::string CopperAxe::getSerializationKey()
{
	return CopperAxe::SaveKey;
}

Size CopperAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 CopperAxe::getWeaponCollisionOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(-12.0f, 212.0f);
}

Vec2 CopperAxe::getDisplayOffset()
{
	return Vec2(20.0f, -4.0f);
}
