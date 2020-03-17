#include "HedgeTrimmer.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HedgeTrimmer::SaveKeyHedgeTrimmer = "hedge-trimmer";

HedgeTrimmer* HedgeTrimmer::create()
{
	HedgeTrimmer* instance = new HedgeTrimmer();

	instance->autorelease();

	return instance;
}

HedgeTrimmer::HedgeTrimmer() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
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

HedgeTrimmer::~HedgeTrimmer()
{
}

Item* HedgeTrimmer::clone()
{
	return HedgeTrimmer::create();
}

std::string HedgeTrimmer::getItemName()
{
	return HedgeTrimmer::SaveKeyHedgeTrimmer;
}

LocalizedString* HedgeTrimmer::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_HedgeTrimmer::create();
}

std::string HedgeTrimmer::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_HedgeTrimmer;
}

std::string HedgeTrimmer::getSerializationKey()
{
	return HedgeTrimmer::SaveKeyHedgeTrimmer;
}

Size HedgeTrimmer::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 HedgeTrimmer::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
