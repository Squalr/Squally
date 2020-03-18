#include "WoodenClub.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WoodenClub::SaveKeyWoodenClub = "wooden-club";

WoodenClub* WoodenClub::create()
{
	WoodenClub* instance = new WoodenClub();

	instance->autorelease();

	return instance;
}

WoodenClub::WoodenClub() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 8, 11, ItemStats(
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

WoodenClub::~WoodenClub()
{
}

Item* WoodenClub::clone()
{
	return WoodenClub::create();
}

std::string WoodenClub::getItemName()
{
	return WoodenClub::SaveKeyWoodenClub;
}

LocalizedString* WoodenClub::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_WoodenClub::create();
}

std::string WoodenClub::getIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_WoodenClub;
}

std::string WoodenClub::getSerializationKey()
{
	return WoodenClub::SaveKeyWoodenClub;
}

Vec2 WoodenClub::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
