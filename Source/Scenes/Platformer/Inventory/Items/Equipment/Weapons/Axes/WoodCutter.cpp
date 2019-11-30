#include "WoodCutter.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodCutter::SaveKeyWoodCutter = "wood-cutter";

WoodCutter* WoodCutter::create()
{
	WoodCutter* instance = new WoodCutter();

	instance->autorelease();

	return instance;
}

WoodCutter::WoodCutter() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 11 }}), 4, 7)
{
}

WoodCutter::~WoodCutter()
{
}

Item* WoodCutter::clone()
{
	return WoodCutter::create();
}

std::string WoodCutter::getItemName()
{
	return WoodCutter::SaveKeyWoodCutter;
}

LocalizedString* WoodCutter::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_WoodCutter::create();
}

std::string WoodCutter::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_WoodCutter;
}

std::string WoodCutter::getSerializationKey()
{
	return WoodCutter::SaveKeyWoodCutter;
}

Size WoodCutter::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 WoodCutter::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
