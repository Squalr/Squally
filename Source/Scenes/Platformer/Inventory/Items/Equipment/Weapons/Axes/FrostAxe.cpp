#include "FrostAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FrostAxe::SaveKey = "frost-axe";

FrostAxe* FrostAxe::create()
{
	FrostAxe* instance = new FrostAxe();

	instance->autorelease();

	return instance;
}

FrostAxe::FrostAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
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

FrostAxe::~FrostAxe()
{
}

Item* FrostAxe::clone()
{
	return FrostAxe::create();
}

std::string FrostAxe::getItemName()
{
	return FrostAxe::SaveKey;
}

LocalizedString* FrostAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_FrostAxe::create();
}

std::string FrostAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_FrostAxe;
}

std::string FrostAxe::getSerializationKey()
{
	return FrostAxe::SaveKey;
}

Size FrostAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 FrostAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
