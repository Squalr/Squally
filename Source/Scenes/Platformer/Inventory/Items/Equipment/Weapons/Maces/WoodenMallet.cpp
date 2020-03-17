#include "WoodenMallet.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenMallet::SaveKeyWoodenMallet = "wooden-mallet";

WoodenMallet* WoodenMallet::create()
{
	WoodenMallet* instance = new WoodenMallet();

	instance->autorelease();

	return instance;
}

WoodenMallet::WoodenMallet() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 5 }}), 6, 8, ItemStats(
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

WoodenMallet::~WoodenMallet()
{
}

Item* WoodenMallet::clone()
{
	return WoodenMallet::create();
}

std::string WoodenMallet::getItemName()
{
	return WoodenMallet::SaveKeyWoodenMallet;
}

LocalizedString* WoodenMallet::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_WoodenMallet::create();
}

std::string WoodenMallet::getIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_WoodenMallet;
}

std::string WoodenMallet::getSerializationKey()
{
	return WoodenMallet::SaveKeyWoodenMallet;
}

Vec2 WoodenMallet::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
