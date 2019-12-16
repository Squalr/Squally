#include "WoodenWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenWand::SaveKeyWoodenWand = "wooden-wand";

WoodenWand* WoodenWand::create()
{
	WoodenWand* instance = new WoodenWand();

	instance->autorelease();

	return instance;
}

WoodenWand::WoodenWand() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 5 }}), 1, 2, ItemStats(
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

WoodenWand::~WoodenWand()
{
}

Item* WoodenWand::clone()
{
	return WoodenWand::create();
}

std::string WoodenWand::getItemName()
{
	return WoodenWand::SaveKeyWoodenWand;
}

LocalizedString* WoodenWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_WoodenWand::create();
}

std::string WoodenWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_WoodenWand;
}

std::string WoodenWand::getSerializationKey()
{
	return WoodenWand::SaveKeyWoodenWand;
}

Vec2 WoodenWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
