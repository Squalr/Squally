#include "BoneAxe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoneAxe::SaveKey = "bone-axe";

BoneAxe* BoneAxe::create()
{
	BoneAxe* instance = new BoneAxe();

	instance->autorelease();

	return instance;
}

BoneAxe::BoneAxe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
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

BoneAxe::~BoneAxe()
{
}

Item* BoneAxe::clone()
{
	return BoneAxe::create();
}

std::string BoneAxe::getItemName()
{
	return BoneAxe::SaveKey;
}

LocalizedString* BoneAxe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_BoneAxe::create();
}

std::string BoneAxe::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_BoneAxe;
}

std::string BoneAxe::getSerializationKey()
{
	return BoneAxe::SaveKey;
}

Size BoneAxe::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 BoneAxe::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}

Vec2 BoneAxe::getDisplayOffset()
{
	return Vec2(28.0f, -4.0f);
}
