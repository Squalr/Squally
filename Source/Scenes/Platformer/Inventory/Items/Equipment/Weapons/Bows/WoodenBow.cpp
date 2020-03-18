#include "WoodenBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenBow::SaveKeyWoodenBow = "wooden-bow";

WoodenBow* WoodenBow::create()
{
	WoodenBow* instance = new WoodenBow();

	instance->autorelease();

	return instance;
}

WoodenBow::WoodenBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 6, 8, ItemStats(
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

WoodenBow::~WoodenBow()
{
}

Item* WoodenBow::clone()
{
	return WoodenBow::create();
}

std::string WoodenBow::getItemName()
{
	return WoodenBow::SaveKeyWoodenBow;
}

LocalizedString* WoodenBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_WoodenBow::create();
}

std::string WoodenBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_WoodenBow;
}

std::string WoodenBow::getSerializationKey()
{
	return WoodenBow::SaveKeyWoodenBow;
}

Vec2 WoodenBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
